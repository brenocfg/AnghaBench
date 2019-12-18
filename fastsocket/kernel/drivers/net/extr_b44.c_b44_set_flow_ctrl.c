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
struct b44 {int dummy; } ;

/* Variables and functions */
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int B44_FLAG_RX_PAUSE ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  __b44_set_flow_ctrl (struct b44*,int) ; 

__attribute__((used)) static void b44_set_flow_ctrl(struct b44 *bp, u32 local, u32 remote)
{
	u32 pause_enab = 0;

	/* The driver supports only rx pause by default because
	   the b44 mac tx pause mechanism generates excessive
	   pause frames.
	   Use ethtool to turn on b44 tx pause if necessary.
	 */
	if ((local & ADVERTISE_PAUSE_CAP) &&
	    (local & ADVERTISE_PAUSE_ASYM)){
		if ((remote & LPA_PAUSE_ASYM) &&
		    !(remote & LPA_PAUSE_CAP))
			pause_enab |= B44_FLAG_RX_PAUSE;
	}

	__b44_set_flow_ctrl(bp, pause_enab);
}