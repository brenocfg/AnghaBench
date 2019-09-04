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
typedef  int /*<<< orphan*/  AVOutputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ; 
 int /*<<< orphan*/  AV_CLASS_CATEGORY_DEVICE_OUTPUT ; 
 int /*<<< orphan*/ * device_next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

AVOutputFormat *av_output_audio_device_next(AVOutputFormat *d)
{
    return device_next(d, 1, AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT,
                       AV_CLASS_CATEGORY_DEVICE_OUTPUT);
}