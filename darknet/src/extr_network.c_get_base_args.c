#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hue; int /*<<< orphan*/  saturation; int /*<<< orphan*/  center; int /*<<< orphan*/  exposure; int /*<<< orphan*/  aspect; int /*<<< orphan*/  angle; int /*<<< orphan*/  max_crop; int /*<<< orphan*/  min_crop; int /*<<< orphan*/  w; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ network ;
struct TYPE_6__ {int /*<<< orphan*/  hue; int /*<<< orphan*/  saturation; int /*<<< orphan*/  center; int /*<<< orphan*/  exposure; int /*<<< orphan*/  aspect; int /*<<< orphan*/  angle; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  size; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ load_args ;

/* Variables and functions */

load_args get_base_args(network *net)
{
    load_args args = {0};
    args.w = net->w;
    args.h = net->h;
    args.size = net->w;

    args.min = net->min_crop;
    args.max = net->max_crop;
    args.angle = net->angle;
    args.aspect = net->aspect;
    args.exposure = net->exposure;
    args.center = net->center;
    args.saturation = net->saturation;
    args.hue = net->hue;
    return args;
}