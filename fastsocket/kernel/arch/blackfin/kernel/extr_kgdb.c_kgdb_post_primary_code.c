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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int gdb_bfin_errcode ; 
 int gdb_bfin_vector ; 

void kgdb_post_primary_code(struct pt_regs *regs, int eVector, int err_code)
{
	/* Master processor is completely in the debugger */
	gdb_bfin_vector = eVector;
	gdb_bfin_errcode = err_code;
}