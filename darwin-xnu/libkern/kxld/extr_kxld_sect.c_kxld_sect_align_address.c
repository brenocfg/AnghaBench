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
typedef  int /*<<< orphan*/  kxld_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  align; } ;
typedef  TYPE_1__ KXLDSect ;

/* Variables and functions */
 int /*<<< orphan*/  kxld_align_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kxld_addr_t
kxld_sect_align_address(const KXLDSect *sect, kxld_addr_t address)
{
    return kxld_align_address(address, sect->align);
}