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
struct pxa25x_udc {int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNABORTED ; 
 unsigned int PXA_UDC_NUM_ENDPOINTS ; 
 int /*<<< orphan*/  nuke (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_ep_state (struct pxa25x_udc *dev)
{
	unsigned i;

	/* hardware SET_{CONFIGURATION,INTERFACE} automagic resets endpoint
	 * fifos, and pending transactions mustn't be continued in any case.
	 */
	for (i = 1; i < PXA_UDC_NUM_ENDPOINTS; i++)
		nuke(&dev->ep[i], -ECONNABORTED);
}