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
typedef  scalar_t__ vm_address_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kernel_mach_header_t ;
struct TYPE_4__ {scalar_t__ numSummaries; TYPE_1__* summaries; } ;
struct TYPE_3__ {scalar_t__ address; scalar_t__ size; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ OSKextLoadedKextSummary ;

/* Variables and functions */
 TYPE_2__* gLoadedKextSummaries ; 
 scalar_t__ panic_print_macho_symbol_name (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
panic_print_kmod_symbol_name(vm_address_t search)
{
    u_int i;

    if (gLoadedKextSummaries == NULL)
	    return;
    for (i = 0; i < gLoadedKextSummaries->numSummaries; ++i) {
        OSKextLoadedKextSummary *summary = gLoadedKextSummaries->summaries + i;

        if ((search >= summary->address) &&
            (search < (summary->address + summary->size)))
        {
            kernel_mach_header_t *header = (kernel_mach_header_t *)(uintptr_t) summary->address;
            if (panic_print_macho_symbol_name(header, search, summary->name) == 0) {
                paniclog_append_noflush("%s + %llu", summary->name, (unsigned long)search - summary->address);
            }
            break;
        }
    }
}