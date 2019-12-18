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
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ff_rtsp_close_connections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_rtsp_close_streams (int /*<<< orphan*/ *) ; 
 int ff_rtsp_connect (int /*<<< orphan*/ *) ; 
 scalar_t__ rtsp_write_record (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtsp_write_header(AVFormatContext *s)
{
    int ret;

    ret = ff_rtsp_connect(s);
    if (ret)
        return ret;

    if (rtsp_write_record(s) < 0) {
        ff_rtsp_close_streams(s);
        ff_rtsp_close_connections(s);
        return AVERROR_INVALIDDATA;
    }
    return 0;
}