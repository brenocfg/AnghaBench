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
struct trapsink_dep {int /*<<< orphan*/  rb_status; } ;
struct trapsink {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int SNMP_ERR_NOERROR ; 

__attribute__((used)) static int
trapsink_undestroy(struct trapsink *t, struct trapsink_dep *tdep)
{
	t->status = tdep->rb_status;
	return (SNMP_ERR_NOERROR);
}