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
struct TYPE_8__ {int (* systemCall ) (int*) ;scalar_t__ dataBase; int /*<<< orphan*/  name; scalar_t__ dllHandle; } ;
typedef  TYPE_1__ vm_t ;
struct TYPE_9__ {scalar_t__ vmMagic; int bssLength; int dataLength; int litLength; scalar_t__ codeLength; int dataOffset; } ;
typedef  TYPE_2__ vmHeader_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Com_Memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  FS_FreeFile (TYPE_2__*) ; 
 int FS_ReadFile (char*,void**) ; 
 int LittleLong (int) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VMI_NATIVE ; 
 TYPE_1__* VM_Create (char*,int (*) (int*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Free (TYPE_1__*) ; 
 scalar_t__ VM_MAGIC ; 

vm_t *VM_Restart( vm_t *vm ) {
	vmHeader_t	*header;
	int			length;
	int			dataLength;
	int			i;
	char		filename[MAX_QPATH];

	// DLL's can't be restarted in place
	if ( vm->dllHandle ) {
		char	name[MAX_QPATH];
	    int			(*systemCall)( int *parms );
		
		systemCall = vm->systemCall;	
		Q_strncpyz( name, vm->name, sizeof( name ) );

		VM_Free( vm );

		vm = VM_Create( name, systemCall, VMI_NATIVE );
		return vm;
	}

	// load the image
	Com_Printf( "VM_Restart()\n", filename );
	Com_sprintf( filename, sizeof(filename), "vm/%s.qvm", vm->name );
	Com_Printf( "Loading vm file %s.\n", filename );
	length = FS_ReadFile( filename, (void **)&header );
	if ( !header ) {
		Com_Error( ERR_DROP, "VM_Restart failed.\n" );
	}

	// byte swap the header
	for ( i = 0 ; i < sizeof( *header ) / 4 ; i++ ) {
		((int *)header)[i] = LittleLong( ((int *)header)[i] );
	}

	// validate
	if ( header->vmMagic != VM_MAGIC
		|| header->bssLength < 0 
		|| header->dataLength < 0 
		|| header->litLength < 0 
		|| header->codeLength <= 0 ) {
		VM_Free( vm );
		Com_Error( ERR_FATAL, "%s has bad header", filename );
	}

	// round up to next power of 2 so all data operations can
	// be mask protected
	dataLength = header->dataLength + header->litLength + header->bssLength;
	for ( i = 0 ; dataLength > ( 1 << i ) ; i++ ) {
	}
	dataLength = 1 << i;

	// clear the data
	Com_Memset( vm->dataBase, 0, dataLength );

	// copy the intialized data
	Com_Memcpy( vm->dataBase, (byte *)header + header->dataOffset, header->dataLength + header->litLength );

	// byte swap the longs
	for ( i = 0 ; i < header->dataLength ; i += 4 ) {
		*(int *)(vm->dataBase + i) = LittleLong( *(int *)(vm->dataBase + i ) );
	}

	// free the original file
	FS_FreeFile( header );

	return vm;
}