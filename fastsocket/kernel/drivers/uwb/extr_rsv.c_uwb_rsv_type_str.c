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
typedef  enum uwb_drp_type { ____Placeholder_uwb_drp_type } uwb_drp_type ;

/* Variables and functions */
 int UWB_DRP_TYPE_ALIEN_BP ; 
 int UWB_DRP_TYPE_PCA ; 
 char const** rsv_types ; 

const char *uwb_rsv_type_str(enum uwb_drp_type type)
{
	if (type < UWB_DRP_TYPE_ALIEN_BP || type > UWB_DRP_TYPE_PCA)
		return "invalid";
	return rsv_types[type];
}