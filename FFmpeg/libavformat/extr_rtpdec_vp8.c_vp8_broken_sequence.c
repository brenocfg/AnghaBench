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
struct TYPE_3__ {int /*<<< orphan*/  data; scalar_t__ sequence_ok; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vp8_broken_sequence(AVFormatContext *ctx, PayloadContext *vp8,
                               const char *msg)
{
    vp8->sequence_ok = 0;
    av_log(ctx, AV_LOG_WARNING, "%s", msg);
    ffio_free_dyn_buf(&vp8->data);
    return AVERROR(EAGAIN);
}