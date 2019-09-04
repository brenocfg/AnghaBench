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
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codec_opts ; 
 int /*<<< orphan*/  format_opts ; 
 int /*<<< orphan*/  resample_opts ; 
 int /*<<< orphan*/  swr_opts ; 
 int /*<<< orphan*/  sws_dict ; 

void uninit_opts(void)
{
    av_dict_free(&swr_opts);
    av_dict_free(&sws_dict);
    av_dict_free(&format_opts);
    av_dict_free(&codec_opts);
    av_dict_free(&resample_opts);
}