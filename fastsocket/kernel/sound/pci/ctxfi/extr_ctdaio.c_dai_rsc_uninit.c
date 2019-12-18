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
struct hw {int /*<<< orphan*/  (* dai_put_ctrl_blk ) (int /*<<< orphan*/ *) ;} ;
struct dai {int /*<<< orphan*/  daio; int /*<<< orphan*/ * ctrl_blk; scalar_t__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  daio_rsc_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dai_rsc_uninit(struct dai *dai)
{
	((struct hw *)dai->hw)->dai_put_ctrl_blk(dai->ctrl_blk);
	dai->hw = dai->ctrl_blk = NULL;
	daio_rsc_uninit(&dai->daio);
	return 0;
}