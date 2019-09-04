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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_3__ {int swfhash_len; int /*<<< orphan*/  swfhash; int /*<<< orphan*/  swfsize; int /*<<< orphan*/ * swfverification; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int) ; 
 int ff_rtmp_calc_digest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtmp_calc_swf_verification(URLContext *s, RTMPContext *rt,
                                      uint8_t *buf)
{
    uint8_t *p;
    int ret;

    if (rt->swfhash_len != 32) {
        av_log(s, AV_LOG_ERROR,
               "Hash of the decompressed SWF file is not 32 bytes long.\n");
        return AVERROR(EINVAL);
    }

    p = &rt->swfverification[0];
    bytestream_put_byte(&p, 1);
    bytestream_put_byte(&p, 1);
    bytestream_put_be32(&p, rt->swfsize);
    bytestream_put_be32(&p, rt->swfsize);

    if ((ret = ff_rtmp_calc_digest(rt->swfhash, 32, 0, buf, 32, p)) < 0)
        return ret;

    return 0;
}