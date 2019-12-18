#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_connections; int /*<<< orphan*/ * open_handle; } ;

/* Variables and functions */
 TYPE_1__ gencmd_client ; 
 int vchi_service_use (int /*<<< orphan*/ ) ; 

int use_gencmd_service(void) {
   int ret = 0;
   int i=0;
   for(i = 0; i < gencmd_client.num_connections; i++) {
      ret = (ret == 0) ? vchi_service_use(gencmd_client.open_handle[i]) : ret;
   }
   return ret;
}