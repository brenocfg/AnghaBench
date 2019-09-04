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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  rtmp; } ;
typedef  int /*<<< orphan*/  RTMP ;
typedef  TYPE_2__ LibRTMPContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int RTMP_Write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int rtmp_write(URLContext *s, const uint8_t *buf, int size)
{
    LibRTMPContext *ctx = s->priv_data;
    RTMP *r = &ctx->rtmp;

    int ret = RTMP_Write(r, buf, size);
    if (!ret)
        return AVERROR_EOF;
    return ret;
}