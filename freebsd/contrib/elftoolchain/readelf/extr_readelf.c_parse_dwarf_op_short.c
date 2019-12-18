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
struct readelf {int /*<<< orphan*/  dop; } ;
struct TYPE_2__ {char const sn; int /*<<< orphan*/  value; int /*<<< orphan*/ * ln; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DEFAULT_OPTIONS ; 
 TYPE_1__* dwarf_op ; 

__attribute__((used)) static void
parse_dwarf_op_short(struct readelf *re, const char *op)
{
	int i;

	if (op == NULL) {
		re->dop |= DW_DEFAULT_OPTIONS;
		return;
	}

	for (; *op != '\0'; op++) {
		for (i = 0; dwarf_op[i].ln != NULL; i++) {
			if (dwarf_op[i].sn == *op) {
				re->dop |= dwarf_op[i].value;
				break;
			}
		}
	}
}