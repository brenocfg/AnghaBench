#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_cropcap {TYPE_1__ pixelaspect; int /*<<< orphan*/  type; } ;
struct AVRational {int member_1; int /*<<< orphan*/  den; int /*<<< orphan*/  num; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  cropcap ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ V4L2Context ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
typedef  struct AVRational AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_CROPCAP ; 
 TYPE_4__* ctx_to_m2mctx (TYPE_2__*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_cropcap*) ; 
 int /*<<< orphan*/  memset (struct v4l2_cropcap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static AVRational v4l2_get_sar(V4L2Context *ctx)
{
    struct AVRational sar = { 0, 1 };
    struct v4l2_cropcap cropcap;
    int ret;

    memset(&cropcap, 0, sizeof(cropcap));
    cropcap.type = ctx->type;

    ret = ioctl(ctx_to_m2mctx(ctx)->fd, VIDIOC_CROPCAP, &cropcap);
    if (ret)
        return sar;

    sar.num = cropcap.pixelaspect.numerator;
    sar.den = cropcap.pixelaspect.denominator;
    return sar;
}