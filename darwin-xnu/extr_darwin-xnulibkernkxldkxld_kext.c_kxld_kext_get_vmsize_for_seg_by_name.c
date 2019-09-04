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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int /*<<< orphan*/  kext; } ;
typedef  TYPE_1__ KXLDKext ;

/* Variables and functions */
 int /*<<< orphan*/  kxld_object_get_vmsize_for_seg_by_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

void
kxld_kext_get_vmsize_for_seg_by_name(const KXLDKext *kext,
                                          const char *segname,
                                          u_long *vmsize)
{
    (void) kxld_object_get_vmsize_for_seg_by_name(kext->kext, segname, vmsize);
}