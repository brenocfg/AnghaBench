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
typedef  int /*<<< orphan*/  hb_subtitle_t ;
typedef  int /*<<< orphan*/  AVCodecParameters ;

/* Variables and functions */
 scalar_t__ ffmpeg_parse_vobsub_extradata_mkv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ffmpeg_parse_vobsub_extradata_mp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffmpeg_parse_vobsub_extradata( AVCodecParameters *codecpar,
                                          hb_subtitle_t *subtitle )
{
    // XXX: Better if we actually chose the correct parser based on the input container
    return
        ffmpeg_parse_vobsub_extradata_mkv(codecpar, subtitle) &&
        ffmpeg_parse_vobsub_extradata_mp4(codecpar, subtitle);
}