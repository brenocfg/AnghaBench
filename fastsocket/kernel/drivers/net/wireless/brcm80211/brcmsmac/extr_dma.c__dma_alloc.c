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
typedef  int /*<<< orphan*/  uint ;
struct dma_info {int dummy; } ;

/* Variables and functions */
 int dma64_alloc (struct dma_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _dma_alloc(struct dma_info *di, uint direction)
{
	return dma64_alloc(di, direction);
}