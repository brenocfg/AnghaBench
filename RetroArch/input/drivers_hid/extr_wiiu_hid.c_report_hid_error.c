#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* driver; } ;
typedef  TYPE_2__ wiiu_adapter_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 

__attribute__((used)) static void report_hid_error(const char *msg, wiiu_adapter_t *adapter, int32_t error)
{
   if (error >= 0)
      return;

   int16_t hid_error_code = error & 0xffff;
   int16_t error_category = (error >> 16) & 0xffff;
   const char *device = (adapter && adapter->driver) ? adapter->driver->name : "unknown";

   switch(hid_error_code)
   {
      case -100:
         RARCH_ERR("[hid]: Invalid RM command (%s)\n", device);
         break;
      case -102:
         RARCH_ERR("[hid]: Invalid IOCTL command (%s)\n", device);
         break;
      case -103:
         RARCH_ERR("[hid]: bad vector count (%s)\n", device);
         break;
      case -104:
         RARCH_ERR("[hid]: invalid memory bank (%s)\n", device);
         break;
      case -105:
         RARCH_ERR("[hid]: invalid memory alignment (%s)\n", device);
         break;
      case -106:
         RARCH_ERR("[hid]: invalid data size (%s)\n", device);
         break;
      case -107:
         RARCH_ERR("[hid]: request cancelled (%s)\n", device);
         break;
      case -108:
         RARCH_ERR("[hid]: request timed out (%s)\n", device);
         break;
      case -109:
         RARCH_ERR("[hid]: request aborted (%s)\n", device);
         break;
      case -110:
         RARCH_ERR("[hid]: client priority error (%s)\n", device);
         break;
      case -111:
         RARCH_ERR("[hid]: invalid device handle (%s)\n", device);
         break;
#if 0
      default:
         RARCH_ERR("[hid]: Unknown error (%d:%d: %s)\n",
            error_category, hid_error_code, device);
#endif
   }
}