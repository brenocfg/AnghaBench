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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_channel_layout (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_init_for_buffer (int /*<<< orphan*/ *,char*,int) ; 

void av_get_channel_layout_string(char *buf, int buf_size,
                                  int nb_channels, uint64_t channel_layout)
{
    AVBPrint bp;

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_bprint_channel_layout(&bp, nb_channels, channel_layout);
}