#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  level; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ MP4DescrParseContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ MAX_LEVEL ; 
#define  MP4DecConfigDescrTag 132 
#define  MP4ESDescrTag 131 
#define  MP4IODescrTag 130 
#define  MP4ODescrTag 129 
#define  MP4SLDescrTag 128 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int ff_mp4_read_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int parse_MP4DecConfigDescrTag (TYPE_1__*,scalar_t__,int) ; 
 int parse_MP4ESDescrTag (TYPE_1__*,scalar_t__,int) ; 
 int parse_MP4IODescrTag (TYPE_1__*,scalar_t__,int) ; 
 int parse_MP4ODescrTag (TYPE_1__*,scalar_t__,int) ; 
 int parse_MP4SLDescrTag (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  update_offsets (int /*<<< orphan*/ *,scalar_t__*,int*) ; 

__attribute__((used)) static int parse_mp4_descr(MP4DescrParseContext *d, int64_t off, int len,
                           int target_tag)
{
    int tag;
    int len1 = ff_mp4_read_descr(d->s, &d->pb, &tag);
    int ret = 0;

    update_offsets(&d->pb, &off, &len);
    if (len < 0 || len1 > len || len1 <= 0) {
        av_log(d->s, AV_LOG_ERROR,
               "Tag %x length violation new length %d bytes remaining %d\n",
               tag, len1, len);
        return AVERROR_INVALIDDATA;
    }

    if (d->level++ >= MAX_LEVEL) {
        av_log(d->s, AV_LOG_ERROR, "Maximum MP4 descriptor level exceeded\n");
        ret = AVERROR_INVALIDDATA;
        goto done;
    }

    if (target_tag && tag != target_tag) {
        av_log(d->s, AV_LOG_ERROR, "Found tag %x expected %x\n", tag,
               target_tag);
        ret = AVERROR_INVALIDDATA;
        goto done;
    }

    switch (tag) {
    case MP4IODescrTag:
        ret = parse_MP4IODescrTag(d, off, len1);
        break;
    case MP4ODescrTag:
        ret = parse_MP4ODescrTag(d, off, len1);
        break;
    case MP4ESDescrTag:
        ret = parse_MP4ESDescrTag(d, off, len1);
        break;
    case MP4DecConfigDescrTag:
        ret = parse_MP4DecConfigDescrTag(d, off, len1);
        break;
    case MP4SLDescrTag:
        ret = parse_MP4SLDescrTag(d, off, len1);
        break;
    }


done:
    d->level--;
    avio_seek(&d->pb, off + len1, SEEK_SET);
    return ret;
}