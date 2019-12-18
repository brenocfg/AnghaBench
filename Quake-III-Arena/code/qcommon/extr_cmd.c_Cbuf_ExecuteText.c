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

/* Variables and functions */
 int /*<<< orphan*/  Cbuf_AddText (char const*) ; 
 int /*<<< orphan*/  Cbuf_Execute () ; 
 int /*<<< orphan*/  Cbuf_InsertText (char const*) ; 
 int /*<<< orphan*/  Cmd_ExecuteString (char const*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
#define  EXEC_APPEND 130 
#define  EXEC_INSERT 129 
#define  EXEC_NOW 128 
 int /*<<< orphan*/  strlen (char const*) ; 

void Cbuf_ExecuteText (int exec_when, const char *text)
{
	switch (exec_when)
	{
	case EXEC_NOW:
		if (text && strlen(text) > 0) {
			Cmd_ExecuteString (text);
		} else {
			Cbuf_Execute();
		}
		break;
	case EXEC_INSERT:
		Cbuf_InsertText (text);
		break;
	case EXEC_APPEND:
		Cbuf_AddText (text);
		break;
	default:
		Com_Error (ERR_FATAL, "Cbuf_ExecuteText: bad exec_when");
	}
}