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
typedef  int u8 ;
struct dummy_ep {TYPE_1__* desc; } ;
struct dummy {struct dummy_ep* ep; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 int DUMMY_ENDPOINTS ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  is_active (struct dummy*) ; 

__attribute__((used)) static struct dummy_ep *find_endpoint (struct dummy *dum, u8 address)
{
	int		i;

	if (!is_active (dum))
		return NULL;
	if ((address & ~USB_DIR_IN) == 0)
		return &dum->ep [0];
	for (i = 1; i < DUMMY_ENDPOINTS; i++) {
		struct dummy_ep	*ep = &dum->ep [i];

		if (!ep->desc)
			continue;
		if (ep->desc->bEndpointAddress == address)
			return ep;
	}
	return NULL;
}