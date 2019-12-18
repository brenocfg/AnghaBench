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
struct hw {int /*<<< orphan*/  (* dai_srt_set_et ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct dai {int /*<<< orphan*/  ctrl_blk; scalar_t__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dai_set_enb_srt(struct dai *dai, unsigned int enb)
{
	((struct hw *)dai->hw)->dai_srt_set_et(dai->ctrl_blk, enb);
	return 0;
}