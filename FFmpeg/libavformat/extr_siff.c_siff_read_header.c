#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * priv_data; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  SIFFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ TAG_SIFF ; 
 scalar_t__ TAG_SOUN ; 
 scalar_t__ TAG_VBV1 ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int siff_parse_soun (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int siff_parse_vbv1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int siff_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    SIFFContext *c  = s->priv_data;
    uint32_t tag;
    int ret;

    if (avio_rl32(pb) != TAG_SIFF)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 4); // ignore size
    tag = avio_rl32(pb);

    if (tag != TAG_VBV1 && tag != TAG_SOUN) {
        av_log(s, AV_LOG_ERROR, "Not a VBV file\n");
        return AVERROR_INVALIDDATA;
    }

    if (tag == TAG_VBV1 && (ret = siff_parse_vbv1(s, c, pb)) < 0)
        return ret;
    if (tag == TAG_SOUN && (ret = siff_parse_soun(s, c, pb)) < 0)
        return ret;
    if (avio_rl32(pb) != MKTAG('B', 'O', 'D', 'Y')) {
        av_log(s, AV_LOG_ERROR, "'BODY' chunk is missing\n");
        return AVERROR_INVALIDDATA;
    }
    avio_skip(pb, 4); // ignore size

    return 0;
}