#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nsymbols; int highest_frag_index; TYPE_1__* symbols; } ;
struct dsp_spos_instance {TYPE_2__ symbol_table; } ;
struct TYPE_3__ {scalar_t__ deleted; } ;

/* Variables and functions */

__attribute__((used)) static int find_free_symbol_index (struct dsp_spos_instance * ins)
{
	int index = ins->symbol_table.nsymbols,i;

	for (i = ins->symbol_table.highest_frag_index; i < ins->symbol_table.nsymbols; ++i) {
		if (ins->symbol_table.symbols[i].deleted) {
			index = i;
			break;
		}
	}

	return index;
}