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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR (char*) ; 
 int /*<<< orphan*/  LOG_STD (char*) ; 
 int vc_tv_power_off () ; 

__attribute__((used)) static int power_off( void )
{
   int ret;

   LOG_STD( "Powering off HDMI");

   ret = vc_tv_power_off();
   if ( ret != 0 )
   {
      LOG_ERR( "Failed to power off HDMI" );
   }

   return ret;
}