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
struct mthca_mtt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtt_buddy; } ;
struct mthca_dev {TYPE_1__ mr_table; } ;

/* Variables and functions */
 struct mthca_mtt* __mthca_alloc_mtt (struct mthca_dev*,int,int /*<<< orphan*/ *) ; 

struct mthca_mtt *mthca_alloc_mtt(struct mthca_dev *dev, int size)
{
	return __mthca_alloc_mtt(dev, size, &dev->mr_table.mtt_buddy);
}