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
struct TYPE_3__ {int vsync_event_pending; } ;
typedef  TYPE_1__ ctr_video_t ;

/* Variables and functions */

__attribute__((used)) static void ctr_vsync_hook(ctr_video_t* ctr)
{
   ctr->vsync_event_pending = false;
}