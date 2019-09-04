#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__* st; } ;
struct TYPE_4__ {int /*<<< orphan*/  codecpar; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_put_wav_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_wfex_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    int ret;
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0);
    ffio_wfourcc(pb, "wfex");
    if ((ret = ff_put_wav_header(s, pb, track->st->codecpar, FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX)) < 0)
        return ret;
    return update_size(pb, pos);
}