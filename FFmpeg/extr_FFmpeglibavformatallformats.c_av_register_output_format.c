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
 int /*<<< orphan*/  av_format_init_next ; 
 int /*<<< orphan*/  av_format_next_init ; 
 int /*<<< orphan*/  ff_thread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void av_register_output_format(AVOutputFormat *format)
{
    ff_thread_once(&av_format_next_init, av_format_init_next);
}