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
struct v4l2_dbg_match {scalar_t__ type; int addr; } ;

/* Variables and functions */
 scalar_t__ V4L2_CHIP_MATCH_HOST ; 

__attribute__((used)) static inline int cx18_av_dbg_match(const struct v4l2_dbg_match *match)
{
	return match->type == V4L2_CHIP_MATCH_HOST && match->addr == 1;
}