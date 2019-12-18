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
struct ins_operands {int /*<<< orphan*/  raw; } ;
struct ins {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ins__raw_scnprintf(struct ins *ins, char *bf, size_t size,
			      struct ins_operands *ops)
{
	return scnprintf(bf, size, "%-6.6s %s", ins->name, ops->raw);
}