#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  errarg; int /*<<< orphan*/  (* errhand ) (TYPE_1__,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  dbg_errarg; int /*<<< orphan*/  (* dbg_errhand ) (TYPE_1__,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int err_error; int err_elferror; char const* err_func; int err_line; char* err_msg; } ;
typedef  TYPE_1__ Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Debug ;

/* Variables and functions */
 TYPE_5__ _libdwarf ; 
 int /*<<< orphan*/  stub1 (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__,int /*<<< orphan*/ ) ; 

void
_dwarf_set_error(Dwarf_Debug dbg, Dwarf_Error *error, int errorcode,
    int elferrorcode, const char *functionname, int linenumber)
{
	Dwarf_Error de;

	de.err_error = errorcode;
	de.err_elferror = elferrorcode;
	de.err_func  = functionname;
	de.err_line  = linenumber;
	de.err_msg[0] = '\0';
	
	/*
	 * If the user supplied a destination for the error, copy the
	 * error descriptor over and return.  Otherwise, if the debug
	 * context is known and has an error handler, invoke that.
	 * Otherwise, if a 'default' error handler was registered,
	 * invoke it.
	 */
	if (error)
		*error = de;
	else if (dbg && dbg->dbg_errhand)
		dbg->dbg_errhand(de, dbg->dbg_errarg);
	else if (_libdwarf.errhand)
		_libdwarf.errhand(de, _libdwarf.errarg);

	/* No handler found, do nothing. */
}