#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int id; } ;
typedef  TYPE_5__ menucommon_s ;
struct TYPE_7__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_8__ {TYPE_1__ field; } ;
struct TYPE_9__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_10__ {TYPE_3__ field; } ;
struct TYPE_12__ {TYPE_2__ port; TYPE_4__ domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  ID_SPECIFYSERVERBACK 129 
#define  ID_SPECIFYSERVERGO 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_6__ s_specifyserver ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

__attribute__((used)) static void SpecifyServer_Event( void* ptr, int event )
{
	char	buff[256];

	switch (((menucommon_s*)ptr)->id)
	{
		case ID_SPECIFYSERVERGO:
			if (event != QM_ACTIVATED)
				break;

			if (s_specifyserver.domain.field.buffer[0])
			{
				strcpy(buff,s_specifyserver.domain.field.buffer);
				if (s_specifyserver.port.field.buffer[0])
					Com_sprintf( buff+strlen(buff), 128, ":%s", s_specifyserver.port.field.buffer );

				trap_Cmd_ExecuteText( EXEC_APPEND, va( "connect %s\n", buff ) );
			}
			break;

		case ID_SPECIFYSERVERBACK:
			if (event != QM_ACTIVATED)
				break;

			UI_PopMenu();
			break;
	}
}