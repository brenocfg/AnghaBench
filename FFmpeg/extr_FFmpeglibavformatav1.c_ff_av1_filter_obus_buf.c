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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int ff_av1_filter_obus (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_av1_filter_obus_buf(const uint8_t *buf, uint8_t **out, int *size)
{
    AVIOContext *pb;
    int ret;

    ret = avio_open_dyn_buf(&pb);
    if (ret < 0)
        return ret;

    ret = ff_av1_filter_obus(pb, buf, *size);
    if (ret < 0)
        return ret;

    av_freep(out);
    *size = avio_close_dyn_buf(pb, out);

    return ret;
}