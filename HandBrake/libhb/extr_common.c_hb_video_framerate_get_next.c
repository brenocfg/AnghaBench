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
typedef  int /*<<< orphan*/  hb_rate_t ;
struct TYPE_2__ {int /*<<< orphan*/  const* next; } ;
typedef  TYPE_1__ hb_rate_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* hb_video_rates_first_item ; 

const hb_rate_t* hb_video_framerate_get_next(const hb_rate_t *last)
{
    if (last == NULL)
    {
        return hb_video_rates_first_item;
    }
    return ((hb_rate_internal_t*)last)->next;
}