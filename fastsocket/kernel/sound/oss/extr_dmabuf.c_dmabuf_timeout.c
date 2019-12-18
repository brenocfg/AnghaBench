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
struct dma_buffparms {int fragment_size; int data_rate; } ;

/* Variables and functions */
 int HZ ; 

__attribute__((used)) static long dmabuf_timeout(struct dma_buffparms *dmap)
{
	long tmout;

	tmout = (dmap->fragment_size * HZ) / dmap->data_rate;
	tmout += HZ / 5;	/* Some safety distance */
	if (tmout < (HZ / 2))
		tmout = HZ / 2;
	if (tmout > 20 * HZ)
		tmout = 20 * HZ;
	return tmout;
}