#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_5__ {int /*<<< orphan*/  nitems; } ;
struct TYPE_6__ {TYPE_1__ relocs; } ;
typedef  TYPE_2__ KXLDSect ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_2__ const*) ; 

u_int 
kxld_sect_get_num_relocs(const KXLDSect *sect)
{
    check(sect);

    return sect->relocs.nitems;
}