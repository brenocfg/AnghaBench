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
struct esp {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,size_t,int) ; 

__attribute__((used)) static dma_addr_t sun3x_esp_map_single(struct esp *esp, void *buf,
				      size_t sz, int dir)
{
	return dma_map_single(esp->dev, buf, sz, dir);
}