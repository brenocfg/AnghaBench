#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t DTRACEOPT_QUIET ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int dt_print_bytes (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,size_t,int,int,int) ; 

__attribute__((used)) static int
dt_print_memory(dtrace_hdl_t *dtp, FILE *fp, caddr_t addr)
{
	int quiet = (dtp->dt_options[DTRACEOPT_QUIET] != DTRACEOPT_UNSET);
	size_t nbytes = *((uintptr_t *) addr);

	return (dt_print_bytes(dtp, fp, addr + sizeof(uintptr_t),
	    nbytes, 50, quiet, 1));
}