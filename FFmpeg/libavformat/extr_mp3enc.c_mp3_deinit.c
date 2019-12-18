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
struct AVFormatContext {TYPE_1__* priv_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  xing_frame; int /*<<< orphan*/  queue_end; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ MP3Context ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_packet_list_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mp3_deinit(struct AVFormatContext *s)
{
    MP3Context *mp3 = s->priv_data;

    ff_packet_list_free(&mp3->queue, &mp3->queue_end);
    av_freep(&mp3->xing_frame);
}