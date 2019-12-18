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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int PL_PEER_E ; 
 int PL_RESET_IN ; 
 int PL_RESET_OUT ; 
 int PL_S_EN ; 
 int /*<<< orphan*/  pl_set_QuickLink_features (struct usbnet*,int) ; 

__attribute__((used)) static int pl_reset(struct usbnet *dev)
{
	/* some units seem to need this reset, others reject it utterly.
	 * FIXME be more like "naplink" or windows drivers.
	 */
	(void) pl_set_QuickLink_features(dev,
		PL_S_EN|PL_RESET_OUT|PL_RESET_IN|PL_PEER_E);
	return 0;
}