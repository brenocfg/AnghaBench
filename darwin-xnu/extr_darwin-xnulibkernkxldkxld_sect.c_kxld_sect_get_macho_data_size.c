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
typedef  scalar_t__ u_long ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ data; } ;
typedef  TYPE_1__ KXLDSect ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 

u_long
kxld_sect_get_macho_data_size(const KXLDSect *sect)
{
    u_long size = 0;

    check(sect);

    if (sect->data) {
        size = (u_long) sect->size;
    }

    return size;
}