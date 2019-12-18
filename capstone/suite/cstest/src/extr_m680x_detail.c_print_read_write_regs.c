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
typedef  int /*<<< orphan*/  csh ;
struct TYPE_3__ {int regs_read_count; int regs_write_count; int /*<<< orphan*/ * regs_write; int /*<<< orphan*/ * regs_read; } ;
typedef  TYPE_1__ cs_detail ;

/* Variables and functions */
 int /*<<< orphan*/  add_str (char**,char*,...) ; 
 int /*<<< orphan*/  cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_read_write_regs(char *result, csh *handle, cs_detail *detail)
{
	int i;

	if (detail->regs_read_count > 0) {
		add_str(&result, "\treading from regs: ");

		for (i = 0; i < detail->regs_read_count; ++i) {
			if (i > 0)
				add_str(&result, ", ");

			add_str(&result, "%s", cs_reg_name(*handle, detail->regs_read[i]));
		}
	}

	if (detail->regs_write_count > 0) {
		add_str(&result, "\twriting to regs: ");

		for (i = 0; i < detail->regs_write_count; ++i) {
			if (i > 0)
				add_str(&result, ", ");

			add_str(&result, "%s", cs_reg_name(*handle, detail->regs_write[i]));
		}
	}
}