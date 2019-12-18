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
typedef  int /*<<< orphan*/  u32 ;
struct lh7a40x_ep {scalar_t__ fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EP0 (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ep_index (struct lh7a40x_ep*) ; 

__attribute__((used)) static __inline__ void lh7a40x_fifo_write(struct lh7a40x_ep *ep,
					  unsigned char *cp, int count)
{
	volatile u32 *fifo = (volatile u32 *)ep->fifo;
	DEBUG_EP0("fifo_write: %d %d\n", ep_index(ep), count);
	while (count--)
		*fifo = *cp++;
}