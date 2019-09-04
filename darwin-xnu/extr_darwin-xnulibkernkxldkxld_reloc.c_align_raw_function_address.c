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
typedef  unsigned long long kxld_addr_t ;
struct TYPE_3__ {int function_align; } ;
typedef  TYPE_1__ KXLDRelocator ;

/* Variables and functions */

__attribute__((used)) static kxld_addr_t
align_raw_function_address(const KXLDRelocator *relocator, kxld_addr_t value)
{
    if (relocator->function_align) { 
        value &= ~((1ULL << relocator->function_align) - 1); 
    }

    return value; 
}