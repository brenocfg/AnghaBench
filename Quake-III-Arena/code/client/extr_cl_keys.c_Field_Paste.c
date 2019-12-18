#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  field_t ;

/* Variables and functions */
 int /*<<< orphan*/  Field_CharEvent (int /*<<< orphan*/ *,char) ; 
 char* Sys_GetClipboardData () ; 
 int /*<<< orphan*/  Z_Free (char*) ; 
 int strlen (char*) ; 

void Field_Paste( field_t *edit ) {
	char	*cbd;
	int		pasteLen, i;

	cbd = Sys_GetClipboardData();

	if ( !cbd ) {
		return;
	}

	// send as if typed, so insert / overstrike works properly
	pasteLen = strlen( cbd );
	for ( i = 0 ; i < pasteLen ; i++ ) {
		Field_CharEvent( edit, cbd[i] );
	}

	Z_Free( cbd );
}