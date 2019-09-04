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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FLV_TAG_TYPE_VIDEO ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_timestamp (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void put_avc_eos_tag(AVIOContext *pb, unsigned ts)
{
    avio_w8(pb, FLV_TAG_TYPE_VIDEO);
    avio_wb24(pb, 5);               /* Tag Data Size */
    put_timestamp(pb, ts);
    avio_wb24(pb, 0);               /* StreamId = 0 */
    avio_w8(pb, 23);                /* ub[4] FrameType = 1, ub[4] CodecId = 7 */
    avio_w8(pb, 2);                 /* AVC end of sequence */
    avio_wb24(pb, 0);               /* Always 0 for AVC EOS. */
    avio_wb32(pb, 16);              /* Size of FLV tag */
}