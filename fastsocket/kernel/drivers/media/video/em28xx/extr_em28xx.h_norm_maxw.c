#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ is_em2800; scalar_t__ max_range_640_480; scalar_t__ is_webcam; } ;
struct em28xx {unsigned int sensor_xres; TYPE_1__ board; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int norm_maxw(struct em28xx *dev)
{
	if (dev->board.is_webcam)
		return dev->sensor_xres;

	if (dev->board.max_range_640_480 || dev->board.is_em2800)
		return 640;

	return 720;
}