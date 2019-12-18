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
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;

/* Variables and functions */
#define  D3DERR_DEVICELOST 130 
#define  D3DERR_DEVICENOTRESET 129 
#define  D3DERR_DRIVERINTERNALERROR 128 
 int /*<<< orphan*/  RARCH_WARN (char*,...) ; 
 scalar_t__ d3d9_reset_internal (void*,int /*<<< orphan*/ *) ; 
 int d3d9_test_cooperative_level (void*) ; 

bool d3d9_reset(void *dev, void *d3dpp)
{
   const char *err = NULL;

   if (d3d9_reset_internal(dev, (D3DPRESENT_PARAMETERS*)d3dpp))
      return true;

   RARCH_WARN("[D3D]: Attempting to recover from dead state...\n");

#ifndef _XBOX
   /* Try to recreate the device completely. */
   switch (d3d9_test_cooperative_level(dev))
   {
      case D3DERR_DEVICELOST:
         err = "DEVICELOST";
         break;

      case D3DERR_DEVICENOTRESET:
         err = "DEVICENOTRESET";
         break;

      case D3DERR_DRIVERINTERNALERROR:
         err = "DRIVERINTERNALERROR";
         break;

      default:
         err = "Unknown";
   }
   RARCH_WARN("[D3D]: recovering from dead state: (%s).\n", err);
#endif

   return false;
}