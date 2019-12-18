#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_5__ {TYPE_1__ field; } ;
struct TYPE_6__ {TYPE_2__ savename; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM_StripExtension (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 int MAX_QPATH ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_3__ saveConfig ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

__attribute__((used)) static void UI_SaveConfigMenu_SaveEvent( void *ptr, int event ) {
	char	configname[MAX_QPATH];

	if( event != QM_ACTIVATED ) {
		return;
	}

	if( !saveConfig.savename.field.buffer[0] ) {
		return;
	}

	COM_StripExtension(saveConfig.savename.field.buffer, configname );
	trap_Cmd_ExecuteText( EXEC_APPEND, va( "writeconfig %s.cfg\n", configname ) );
	UI_PopMenu();
}