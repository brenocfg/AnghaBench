#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int downloadClientBlock; scalar_t__* downloadBlockSize; int /*<<< orphan*/  downloadSendTime; int /*<<< orphan*/  downloadName; } ;
typedef  TYPE_1__ client_t ;
struct TYPE_9__ {int clients; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t MAX_DOWNLOAD_WINDOW ; 
 int /*<<< orphan*/  SV_CloseDownload (TYPE_1__*) ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_1__*,char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 TYPE_2__ svs ; 

void SV_NextDownload_f( client_t *cl )
{
	int block = atoi( Cmd_Argv(1) );

	if (block == cl->downloadClientBlock) {
		Com_DPrintf( "clientDownload: %d : client acknowledge of block %d\n", cl - svs.clients, block );

		// Find out if we are done.  A zero-length block indicates EOF
		if (cl->downloadBlockSize[cl->downloadClientBlock % MAX_DOWNLOAD_WINDOW] == 0) {
			Com_Printf( "clientDownload: %d : file \"%s\" completed\n", cl - svs.clients, cl->downloadName );
			SV_CloseDownload( cl );
			return;
		}

		cl->downloadSendTime = svs.time;
		cl->downloadClientBlock++;
		return;
	}
	// We aren't getting an acknowledge for the correct block, drop the client
	// FIXME: this is bad... the client will never parse the disconnect message
	//			because the cgame isn't loaded yet
	SV_DropClient( cl, "broken download" );
}