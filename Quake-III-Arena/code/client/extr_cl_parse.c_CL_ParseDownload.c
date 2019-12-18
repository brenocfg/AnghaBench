#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_2__ {scalar_t__ downloadSize; int downloadBlock; scalar_t__ downloadCount; scalar_t__* downloadName; scalar_t__* downloadTempName; scalar_t__ download; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AddReliableCommand (char*) ; 
 int /*<<< orphan*/  CL_NextDownload () ; 
 int /*<<< orphan*/  CL_WritePacket () ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int,int) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,scalar_t__) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 scalar_t__ FS_SV_FOpenFileWrite (scalar_t__*) ; 
 int /*<<< orphan*/  FS_SV_Rename (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FS_Write (unsigned char*,int,scalar_t__) ; 
 int MAX_MSGLEN ; 
 int /*<<< orphan*/  MSG_ReadData (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ MSG_ReadLong (int /*<<< orphan*/ *) ; 
 int MSG_ReadShort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ReadString (int /*<<< orphan*/ *) ; 
 TYPE_1__ clc ; 
 char* va (char*,int) ; 

void CL_ParseDownload ( msg_t *msg ) {
	int		size;
	unsigned char data[MAX_MSGLEN];
	int block;

	// read the data
	block = MSG_ReadShort ( msg );

	if ( !block )
	{
		// block zero is special, contains file size
		clc.downloadSize = MSG_ReadLong ( msg );

		Cvar_SetValue( "cl_downloadSize", clc.downloadSize );

		if (clc.downloadSize < 0)
		{
			Com_Error(ERR_DROP, MSG_ReadString( msg ) );
			return;
		}
	}

	size = MSG_ReadShort ( msg );
	if (size > 0)
		MSG_ReadData( msg, data, size );

	if (clc.downloadBlock != block) {
		Com_DPrintf( "CL_ParseDownload: Expected block %d, got %d\n", clc.downloadBlock, block);
		return;
	}

	// open the file if not opened yet
	if (!clc.download)
	{
		if (!*clc.downloadTempName) {
			Com_Printf("Server sending download, but no download was requested\n");
			CL_AddReliableCommand( "stopdl" );
			return;
		}

		clc.download = FS_SV_FOpenFileWrite( clc.downloadTempName );

		if (!clc.download) {
			Com_Printf( "Could not create %s\n", clc.downloadTempName );
			CL_AddReliableCommand( "stopdl" );
			CL_NextDownload();
			return;
		}
	}

	if (size)
		FS_Write( data, size, clc.download );

	CL_AddReliableCommand( va("nextdl %d", clc.downloadBlock) );
	clc.downloadBlock++;

	clc.downloadCount += size;

	// So UI gets access to it
	Cvar_SetValue( "cl_downloadCount", clc.downloadCount );

	if (!size) { // A zero length block means EOF
		if (clc.download) {
			FS_FCloseFile( clc.download );
			clc.download = 0;

			// rename the file
			FS_SV_Rename ( clc.downloadTempName, clc.downloadName );
		}
		*clc.downloadTempName = *clc.downloadName = 0;
		Cvar_Set( "cl_downloadName", "" );

		// send intentions now
		// We need this because without it, we would hold the last nextdl and then start
		// loading right away.  If we take a while to load, the server is happily trying
		// to send us that last block over and over.
		// Write it twice to help make sure we acknowledge the download
		CL_WritePacket();
		CL_WritePacket();

		// get another file if needed
		CL_NextDownload ();
	}
}