#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  codec_tag; } ;
struct TYPE_4__ {int tag; TYPE_3__* par; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bswap16 (int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int ff_put_wav_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_ms_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    int ret;
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0);
    avio_wl32(pb, track->tag); // store it byteswapped
    track->par->codec_tag = av_bswap16(track->tag >> 16);
    if ((ret = ff_put_wav_header(s, pb, track->par, 0)) < 0)
        return ret;
    return update_size(pb, pos);
}