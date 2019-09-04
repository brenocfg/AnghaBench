#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  kxld_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  is_32_bit; } ;
typedef  TYPE_1__ KXLDRelocator ;

/* Variables and functions */
 int /*<<< orphan*/  KXLD_3264_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pointer_at_addr_32 ; 
 int /*<<< orphan*/  get_pointer_at_addr_64 ; 

kxld_addr_t
kxld_relocator_get_pointer_at_addr(const KXLDRelocator *relocator,
    const u_char *data, u_long offset)
{
    kxld_addr_t value;

    KXLD_3264_FUNC(relocator->is_32_bit, value,
        get_pointer_at_addr_32, get_pointer_at_addr_64,
        relocator, data, offset);

    return value;
}