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
struct TYPE_2__ {int /*<<< orphan*/  ops; int /*<<< orphan*/ * ins; } ;
struct ins_operands {TYPE_1__ locked; } ;
struct ins {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ins__raw_scnprintf (struct ins*,char*,size_t,struct ins_operands*) ; 
 int ins__scnprintf (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lock__scnprintf(struct ins *ins, char *bf, size_t size,
			   struct ins_operands *ops)
{
	int printed;

	if (ops->locked.ins == NULL)
		return ins__raw_scnprintf(ins, bf, size, ops);

	printed = scnprintf(bf, size, "%-6.6s ", ins->name);
	return printed + ins__scnprintf(ops->locked.ins, bf + printed,
					size - printed, ops->locked.ops);
}