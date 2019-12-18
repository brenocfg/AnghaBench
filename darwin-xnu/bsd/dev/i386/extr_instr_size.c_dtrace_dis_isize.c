#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  scalar_t__ model_t ;
typedef  scalar_t__ dis_isize_t ;
struct TYPE_3__ {void** d86_data; int d86_len; int d86_memsize; int d86_rmindex; int /*<<< orphan*/ * d86_check_func; int /*<<< orphan*/  d86_get_byte; } ;
typedef  TYPE_1__ dis86_t ;

/* Variables and functions */
 scalar_t__ DATAMODEL_LP64 ; 
 scalar_t__ DIS_ISIZE_INSTR ; 
 int /*<<< orphan*/  SIZE32 ; 
 int /*<<< orphan*/  SIZE64 ; 
 int /*<<< orphan*/  dtrace_dis_get_byte ; 
 scalar_t__ dtrace_disx86 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_dis_isize(uchar_t *instr, dis_isize_t which, model_t model, int *rmindex)
{
	int sz;
	dis86_t	x;
	uint_t mode = SIZE32;

	mode = (model == DATAMODEL_LP64) ? SIZE64 : SIZE32;

	x.d86_data = (void **)&instr;
	x.d86_get_byte = dtrace_dis_get_byte;
	x.d86_check_func = NULL;

	if (dtrace_disx86(&x, mode) != 0)
		return (-1);

	if (which == DIS_ISIZE_INSTR)
		sz = x.d86_len;		/* length of the instruction */
	else
		sz = x.d86_memsize;	/* length of memory operand */

	if (rmindex != NULL)
		*rmindex = x.d86_rmindex;
	return (sz);
}