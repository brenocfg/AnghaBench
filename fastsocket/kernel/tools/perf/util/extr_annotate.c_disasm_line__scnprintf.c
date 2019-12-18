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
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct disasm_line {TYPE_1__ ops; int /*<<< orphan*/  ins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ins__scnprintf (int /*<<< orphan*/ ,char*,size_t,TYPE_1__*) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int disasm_line__scnprintf(struct disasm_line *dl, char *bf, size_t size, bool raw)
{
	if (raw || !dl->ins)
		return scnprintf(bf, size, "%-6.6s %s", dl->name, dl->ops.raw);

	return ins__scnprintf(dl->ins, bf, size, &dl->ops);
}