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
struct fore200e {int loop_mode; } ;

/* Variables and functions */
#define  ATM_LM_LOC_PHY 130 
#define  ATM_LM_NONE 129 
#define  ATM_LM_RMT_PHY 128 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  SUNI_MCT ; 
 int SUNI_MCT_DLE ; 
 int SUNI_MCT_LLE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int fore200e_set_oc3 (struct fore200e*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
fore200e_setloop(struct fore200e* fore200e, int loop_mode)
{
    u32 mct_value, mct_mask;
    int error;

    if (!capable(CAP_NET_ADMIN))
	return -EPERM;
    
    switch (loop_mode) {

    case ATM_LM_NONE:
	mct_value = 0; 
	mct_mask  = SUNI_MCT_DLE | SUNI_MCT_LLE;
	break;
	
    case ATM_LM_LOC_PHY:
	mct_value = mct_mask = SUNI_MCT_DLE;
	break;

    case ATM_LM_RMT_PHY:
	mct_value = mct_mask = SUNI_MCT_LLE;
	break;

    default:
	return -EINVAL;
    }

    error = fore200e_set_oc3(fore200e, SUNI_MCT, mct_value, mct_mask);
    if (error == 0)
	fore200e->loop_mode = loop_mode;

    return error;
}