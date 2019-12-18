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
struct TYPE_4__ {int /*<<< orphan*/  relocs; scalar_t__ reserved2; scalar_t__ reserved1; scalar_t__ align; scalar_t__ flags; scalar_t__ size; scalar_t__ link_addr; scalar_t__ base_addr; int /*<<< orphan*/ * data; int /*<<< orphan*/  segname; int /*<<< orphan*/  sectname; scalar_t__ allocated; } ;
typedef  TYPE_1__ KXLDSect ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
kxld_sect_clear(KXLDSect *sect)
{
    check(sect);

    if (sect->allocated) {
        kxld_free(sect->data, (u_long) sect->size);
        sect->allocated = FALSE;
    }

    bzero(sect->sectname, sizeof(sect->sectname));
    bzero(sect->segname, sizeof(sect->segname));
    sect->data = NULL;
    sect->base_addr = 0;
    sect->link_addr = 0;
    sect->size = 0;
    sect->flags = 0;
    sect->align = 0;
    sect->reserved1 = 0;
    sect->reserved2 = 0;
    kxld_array_clear(&sect->relocs);
}