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
typedef  int u32 ;
struct s3c_hsotg_ep {int dir_in; } ;
struct s3c_hsotg {struct s3c_hsotg_ep* eps; } ;

/* Variables and functions */
 int S3C_HSOTG_EPS ; 
 int USB_DIR_IN ; 

__attribute__((used)) static struct s3c_hsotg_ep *ep_from_windex(struct s3c_hsotg *hsotg,
					   u32 windex)
{
	struct s3c_hsotg_ep *ep = &hsotg->eps[windex & 0x7F];
	int dir = (windex & USB_DIR_IN) ? 1 : 0;
	int idx = windex & 0x7F;

	if (windex >= 0x100)
		return NULL;

	if (idx > S3C_HSOTG_EPS)
		return NULL;

	if (idx && ep->dir_in != dir)
		return NULL;

	return ep;
}