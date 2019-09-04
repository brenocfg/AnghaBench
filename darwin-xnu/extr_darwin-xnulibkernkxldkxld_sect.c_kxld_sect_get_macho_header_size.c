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
typedef  int u_long ;
struct section_64 {int dummy; } ;
struct section {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */

u_long
kxld_sect_get_macho_header_size(boolean_t is_32_bit)
{
    if (is_32_bit) {
        return sizeof(struct section);
    } else {
        return sizeof(struct section_64);
    }
}