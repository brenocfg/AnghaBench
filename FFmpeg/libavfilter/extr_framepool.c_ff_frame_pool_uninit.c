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
struct TYPE_4__ {int /*<<< orphan*/ * pools; } ;
typedef  TYPE_1__ FFFramePool ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_pool_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void ff_frame_pool_uninit(FFFramePool **pool)
{
    int i;

    if (!pool || !*pool)
        return;

    for (i = 0; i < 4; i++) {
        av_buffer_pool_uninit(&(*pool)->pools[i]);
    }

    av_freep(pool);
}