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
struct hw {int /*<<< orphan*/  (* dai_srt_set_rsr ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct dai {int /*<<< orphan*/  ctrl_blk; scalar_t__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dai_set_srt_msr(struct dai *dai, unsigned int msr)
{
	unsigned int rsr;

	for (rsr = 0; msr > 1; msr >>= 1)
		rsr++;

	((struct hw *)dai->hw)->dai_srt_set_rsr(dai->ctrl_blk, rsr);
	return 0;
}