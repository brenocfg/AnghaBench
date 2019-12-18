#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int playlist; } ;
typedef  TYPE_1__ BLURAY_TITLE_INFO ;

/* Variables and functions */

__attribute__((used)) static int title_info_compare_mpls(const void *va, const void *vb)
{
    BLURAY_TITLE_INFO *a, *b;

    a = *(BLURAY_TITLE_INFO**)va;
    b = *(BLURAY_TITLE_INFO**)vb;

    return a->playlist - b->playlist;
}