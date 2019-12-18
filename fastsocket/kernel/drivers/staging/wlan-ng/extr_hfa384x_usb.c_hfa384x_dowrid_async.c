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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  hfa384x_t ;
typedef  int /*<<< orphan*/  ctlx_usercb_t ;
typedef  int /*<<< orphan*/  ctlx_cmdcb_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOASYNC ; 
 int hfa384x_dowrid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int
hfa384x_dowrid_async(hfa384x_t *hw,
		     u16 rid, void *riddata, unsigned int riddatalen,
		     ctlx_cmdcb_t cmdcb,
		     ctlx_usercb_t usercb, void *usercb_data)
{
	return hfa384x_dowrid(hw, DOASYNC,
			      rid, riddata, riddatalen,
			      cmdcb, usercb, usercb_data);
}