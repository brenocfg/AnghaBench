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

__attribute__((used)) static void srt_move_cb(void *priv, int x1, int y1, int x2, int y2,
                        int t1, int t2)
{
    // TODO: add a AV_PKT_DATA_SUBTITLE_POSITION side data when a new subtitles
    // encoding API passing the AVPacket is available.
}