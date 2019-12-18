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
typedef  int /*<<< orphan*/  uint8_t ;
struct vsframe_ref_data {int /*<<< orphan*/  vss_state; scalar_t__ frame; TYPE_1__* vsapi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* freeFrame ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (struct vsframe_ref_data*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void free_vsframe_ref(void *opaque, uint8_t *data)
{
    struct vsframe_ref_data *d = opaque;

    if (d->frame)
        d->vsapi->freeFrame(d->frame);

    av_buffer_unref(&d->vss_state);

    av_free(d);
}