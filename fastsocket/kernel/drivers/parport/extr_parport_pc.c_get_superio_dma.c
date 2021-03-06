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
struct superio_struct {int dma; } ;
struct parport {int dummy; } ;

/* Variables and functions */
 int PARPORT_DMA_NONE ; 
 struct superio_struct* find_superio (struct parport*) ; 

__attribute__((used)) static int get_superio_dma(struct parport *p)
{
	struct superio_struct *s = find_superio(p);
	if (s)
		return s->dma;
	return PARPORT_DMA_NONE;
}