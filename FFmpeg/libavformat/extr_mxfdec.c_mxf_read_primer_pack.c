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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  UID ;
struct TYPE_2__ {int local_tags_count; scalar_t__ local_tags; int /*<<< orphan*/  fc; } ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_calloc (int,int) ; 
 int /*<<< orphan*/  av_free (scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int mxf_read_primer_pack(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFContext *mxf = arg;
    int item_num = avio_rb32(pb);
    int item_len = avio_rb32(pb);

    if (item_len != 18) {
        avpriv_request_sample(pb, "Primer pack item length %d", item_len);
        return AVERROR_PATCHWELCOME;
    }
    if (item_num > 65536 || item_num < 0) {
        av_log(mxf->fc, AV_LOG_ERROR, "item_num %d is too large\n", item_num);
        return AVERROR_INVALIDDATA;
    }
    if (mxf->local_tags)
        av_log(mxf->fc, AV_LOG_VERBOSE, "Multiple primer packs\n");
    av_free(mxf->local_tags);
    mxf->local_tags_count = 0;
    mxf->local_tags = av_calloc(item_num, item_len);
    if (!mxf->local_tags)
        return AVERROR(ENOMEM);
    mxf->local_tags_count = item_num;
    avio_read(pb, mxf->local_tags, item_num*item_len);
    return 0;
}