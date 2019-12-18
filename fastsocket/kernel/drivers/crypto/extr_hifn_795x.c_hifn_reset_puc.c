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
struct hifn_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_0_PUCTRL ; 
 int /*<<< orphan*/  HIFN_PUCTRL_DMAENA ; 
 int /*<<< orphan*/  hifn_wait_puc (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_write_0 (struct hifn_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hifn_reset_puc(struct hifn_device *dev)
{
	hifn_write_0(dev, HIFN_0_PUCTRL, HIFN_PUCTRL_DMAENA);
	hifn_wait_puc(dev);
}