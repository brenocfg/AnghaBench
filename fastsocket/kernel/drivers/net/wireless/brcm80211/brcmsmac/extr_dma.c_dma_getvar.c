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
struct dma_pub {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  txavail; } ;
struct dma_info {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

unsigned long dma_getvar(struct dma_pub *pub, const char *name)
{
	struct dma_info *di = (struct dma_info *)pub;

	if (!strcmp(name, "&txavail"))
		return (unsigned long)&(di->dma.txavail);
	return 0;
}