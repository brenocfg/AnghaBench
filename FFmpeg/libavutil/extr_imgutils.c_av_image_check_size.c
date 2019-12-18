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

/* Variables and functions */
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  INT64_MAX ; 
 int av_image_check_size2 (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

int av_image_check_size(unsigned int w, unsigned int h, int log_offset, void *log_ctx)
{
    return av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}