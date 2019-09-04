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
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTABLE_ENTRY_SIZE_32 ; 
 int /*<<< orphan*/  VTABLE_ENTRY_SIZE_64 ; 
 int /*<<< orphan*/  VTABLE_HEADER_SIZE_32 ; 
 int /*<<< orphan*/  VTABLE_HEADER_SIZE_64 ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
get_vtable_base_sizes(boolean_t is_32_bit, u_int *vtable_entry_size,
    u_int *vtable_header_size)
{
    check(vtable_entry_size);
    check(vtable_header_size);

    if (is_32_bit) {
        *vtable_entry_size = VTABLE_ENTRY_SIZE_32;
        *vtable_header_size = VTABLE_HEADER_SIZE_32;
    } else {
        *vtable_entry_size = VTABLE_ENTRY_SIZE_64;
        *vtable_header_size = VTABLE_HEADER_SIZE_64;
    }
}