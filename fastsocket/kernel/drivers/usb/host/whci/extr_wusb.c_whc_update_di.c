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
typedef  int u32 ;
struct whc {scalar_t__ base; TYPE_1__* umc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WUSBDIBUPDATED ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int whci_wait_for (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int whc_update_di(struct whc *whc, int idx)
{
	int offset = idx / 32;
	u32 bit = 1 << (idx % 32);

	le_writel(bit, whc->base + WUSBDIBUPDATED + offset);

	return whci_wait_for(&whc->umc->dev,
			     whc->base + WUSBDIBUPDATED + offset, bit, 0,
			     100, "DI update");
}