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
struct bcma_drv_cc {TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int bcma_sflash_init(struct bcma_drv_cc *cc)
{
	bcma_err(cc->core->bus, "Serial flash not supported\n");
	return 0;
}