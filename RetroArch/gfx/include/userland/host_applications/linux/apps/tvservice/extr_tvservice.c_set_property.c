#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_3__ {void* param2; void* param1; int /*<<< orphan*/  property; } ;
typedef  int /*<<< orphan*/  HDMI_PROPERTY_T ;
typedef  TYPE_1__ HDMI_PROPERTY_PARAM_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR (char*,int /*<<< orphan*/ ) ; 
 int vc_tv_hdmi_set_property (TYPE_1__*) ; 

__attribute__((used)) static int set_property(HDMI_PROPERTY_T prop, uint32_t param1, uint32_t param2)
{
   int ret;
   HDMI_PROPERTY_PARAM_T property;
   property.property = prop;
   property.param1 = param1;
   property.param2 = param2;
   //LOG_DBG( "Setting property %d with params %d, %d", prop, param1, param2);
   ret = vc_tv_hdmi_set_property(&property);
   if(ret != 0)
   {
      LOG_ERR( "Failed to set property %d", prop);
   }
   return ret;
}