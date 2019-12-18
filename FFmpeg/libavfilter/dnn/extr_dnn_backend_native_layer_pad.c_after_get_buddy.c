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
typedef  scalar_t__ LayerPadModeParam ;

/* Variables and functions */
 scalar_t__ LPMP_REFLECT ; 
 scalar_t__ LPMP_SYMMETRIC ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int after_get_buddy(int given, int border, LayerPadModeParam mode)
{
    if (mode == LPMP_SYMMETRIC) {
        int offset = given - border;
        return (border - 1 - offset);
    } else if (mode == LPMP_REFLECT) {
        int offset = given - border;
        return (border - 2 - offset);
    } else {
        av_assert0(!"should not reach here");
        return 0;
    }
}