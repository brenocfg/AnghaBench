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
struct v4l2_dbg_match {int type; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  V4L2_CHIP_MATCH_HOST 128 

int v4l2_chip_match_host(const struct v4l2_dbg_match *match)
{
	switch (match->type) {
	case V4L2_CHIP_MATCH_HOST:
		return match->addr == 0;
	default:
		return 0;
	}
}