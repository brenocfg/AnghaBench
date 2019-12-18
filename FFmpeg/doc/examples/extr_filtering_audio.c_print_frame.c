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
typedef  int uint16_t ;
struct TYPE_3__ {int nb_samples; scalar_t__* data; int /*<<< orphan*/  channel_layout; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void print_frame(const AVFrame *frame)
{
    const int n = frame->nb_samples * av_get_channel_layout_nb_channels(frame->channel_layout);
    const uint16_t *p     = (uint16_t*)frame->data[0];
    const uint16_t *p_end = p + n;

    while (p < p_end) {
        fputc(*p    & 0xff, stdout);
        fputc(*p>>8 & 0xff, stdout);
        p++;
    }
    fflush(stdout);
}