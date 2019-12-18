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
struct TYPE_3__ {int (* read_packet ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;scalar_t__ max_packet_size; int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_packet_wrapper(AVIOContext *s, uint8_t *buf, int size)
{
    int ret;

    if (!s->read_packet)
        return AVERROR(EINVAL);
    ret = s->read_packet(s->opaque, buf, size);
#if FF_API_OLD_AVIO_EOF_0
    if (!ret && !s->max_packet_size) {
        av_log(NULL, AV_LOG_WARNING, "Invalid return value 0 for stream protocol\n");
        ret = AVERROR_EOF;
    }
#else
    av_assert2(ret || s->max_packet_size);
#endif
    return ret;
}