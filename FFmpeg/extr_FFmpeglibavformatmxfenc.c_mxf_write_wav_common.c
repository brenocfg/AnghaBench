#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  UID ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int block_align; int sample_rate; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxf_write_generic_sound_common (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mxf_write_local_tag (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int64_t mxf_write_wav_common(AVFormatContext *s, AVStream *st, const UID key)
{
    AVIOContext *pb = s->pb;
    int64_t pos = mxf_write_generic_sound_common(s, st, key);

    mxf_write_local_tag(pb, 2, 0x3D0A);
    avio_wb16(pb, st->codecpar->block_align);

    // avg bytes per sec
    mxf_write_local_tag(pb, 4, 0x3D09);
    avio_wb32(pb, st->codecpar->block_align*st->codecpar->sample_rate);

    return pos;
}