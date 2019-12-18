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
struct TYPE_2__ {int /*<<< orphan*/  menu_filter; } ;
typedef  TYPE_1__ ps2_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_FILTER_LINEAR ; 
 int /*<<< orphan*/  GS_FILTER_NEAREST ; 

__attribute__((used)) static void ps2_set_filtering(void *data, unsigned index, bool smooth)
{
   ps2_video_t *ps2 = (ps2_video_t*)data;

   ps2->menu_filter = smooth ? GS_FILTER_LINEAR : GS_FILTER_NEAREST;
}