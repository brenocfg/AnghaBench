#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ AVOutputFormat ;
typedef  TYPE_2__ AVInputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_register_devices_mutex ; 
 scalar_t__* demuxer_list ; 
 int /*<<< orphan*/  ff_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__* indev_list ; 
 scalar_t__* muxer_list ; 
 scalar_t__* outdev_list ; 

__attribute__((used)) static void av_format_init_next(void)
{
    AVOutputFormat *prevout = NULL, *out;
    AVInputFormat *previn = NULL, *in;

    ff_mutex_lock(&avpriv_register_devices_mutex);

    for (int i = 0; (out = (AVOutputFormat*)muxer_list[i]); i++) {
        if (prevout)
            prevout->next = out;
        prevout = out;
    }

    if (outdev_list) {
        for (int i = 0; (out = (AVOutputFormat*)outdev_list[i]); i++) {
            if (prevout)
                prevout->next = out;
            prevout = out;
        }
    }

    for (int i = 0; (in = (AVInputFormat*)demuxer_list[i]); i++) {
        if (previn)
            previn->next = in;
        previn = in;
    }

    if (indev_list) {
        for (int i = 0; (in = (AVInputFormat*)indev_list[i]); i++) {
            if (previn)
                previn->next = in;
            previn = in;
        }
    }

    ff_mutex_unlock(&avpriv_register_devices_mutex);
}