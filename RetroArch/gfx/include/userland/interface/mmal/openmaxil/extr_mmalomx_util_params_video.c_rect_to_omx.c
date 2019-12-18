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
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_offset; int /*<<< orphan*/  x_offset; } ;
typedef  TYPE_1__ OMX_DISPLAYRECTTYPE ;
typedef  TYPE_2__ MMAL_RECT_T ;

/* Variables and functions */

__attribute__((used)) static void rect_to_omx(OMX_DISPLAYRECTTYPE *dst, const MMAL_RECT_T *src)
{
   dst->x_offset  = src->x;
   dst->y_offset  = src->y;
   dst->width     = src->width;
   dst->height    = src->height;
}