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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ HDMI_RES_GROUP_T ;

/* Variables and functions */
 scalar_t__ HDMI_RES_GROUP_CEA ; 
 scalar_t__ HDMI_RES_GROUP_DMT ; 
 int /*<<< orphan*/  LOG_ERR (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_STD (char*,char*,int /*<<< orphan*/ ) ; 
 int vc_tv_hdmi_power_on_explicit (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int power_on_explicit( HDMI_RES_GROUP_T group,
                              uint32_t mode, uint32_t drive )
{
   int ret;

   LOG_STD( "Powering on HDMI with explicit settings (%s mode %u)",
            group == HDMI_RES_GROUP_CEA ? "CEA" : group == HDMI_RES_GROUP_DMT ? "DMT" : "CUSTOM", mode );

   ret = vc_tv_hdmi_power_on_explicit( drive, group, mode );
   if ( ret != 0 )
   {
      LOG_ERR( "Failed to power on HDMI with explicit settings (%s mode %u)",
               group == HDMI_RES_GROUP_CEA ? "CEA" : group == HDMI_RES_GROUP_DMT ? "DMT" : "CUSTOM", mode );
   }

   return ret;
}