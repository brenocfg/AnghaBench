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
struct linkedit_data_command {int /*<<< orphan*/  has_splitinfolc; int /*<<< orphan*/  datasize; int /*<<< orphan*/  dataoff; int /*<<< orphan*/  cmdsize; } ;
typedef  struct linkedit_data_command KXLDsplitinfolc ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check (struct linkedit_data_command*) ; 

void
kxld_splitinfolc_init_from_macho(KXLDsplitinfolc *splitinfolc, struct linkedit_data_command *src)
{
    check(splitinfolc);
    check(src);

    splitinfolc->cmdsize = src->cmdsize;
    splitinfolc->dataoff = src->dataoff;
    splitinfolc->datasize = src->datasize;
    splitinfolc->has_splitinfolc = TRUE;
}