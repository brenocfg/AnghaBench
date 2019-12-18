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
struct TYPE_3__ {int /*<<< orphan*/  ffmpeg_pkt; int /*<<< orphan*/  ffmpeg_ic; } ;
typedef  TYPE_1__ hb_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffmpeg_close( hb_stream_t *d )
{
    avformat_close_input( &d->ffmpeg_ic );
    av_packet_unref(&d->ffmpeg_pkt);
}