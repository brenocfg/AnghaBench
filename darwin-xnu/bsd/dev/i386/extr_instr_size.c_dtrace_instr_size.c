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
typedef  int /*<<< orphan*/  uchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATAMODEL_NATIVE ; 
 int /*<<< orphan*/  DIS_ISIZE_INSTR ; 
 int dtrace_dis_isize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dtrace_instr_size(uchar_t *instr)
{
	return (dtrace_dis_isize(instr, DIS_ISIZE_INSTR, DATAMODEL_NATIVE,
	    NULL));
}