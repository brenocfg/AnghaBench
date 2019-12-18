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
struct fileport_fdtype_args {TYPE_1__* ffa_pfi; TYPE_1__* ffa_pfi_end; } ;
struct fileglob {int dummy; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ file_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  proc_fileport; scalar_t__ proc_fdtype; } ;

/* Variables and functions */
 scalar_t__ DTYPE_ATALK ; 
 scalar_t__ FILEGLOB_DTYPE (struct fileglob*) ; 
 scalar_t__ PROX_FDTYPE_ATALK ; 

__attribute__((used)) static int
proc_fileport_fdtype(mach_port_name_t name, struct fileglob *fg, void *arg)
{
	struct fileport_fdtype_args *ffa = arg;

	if (ffa->ffa_pfi != ffa->ffa_pfi_end) {
		file_type_t fdtype = FILEGLOB_DTYPE(fg);

		ffa->ffa_pfi->proc_fdtype = (fdtype != DTYPE_ATALK) ?
			fdtype : PROX_FDTYPE_ATALK;
		ffa->ffa_pfi->proc_fileport = name;
		ffa->ffa_pfi++;
		return (0);		/* keep walking */
	} else
		return (-1);		/* stop the walk! */
}