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
struct hidpad_retrode_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct hidpad_retrode_data*) ; 
 scalar_t__ port_count ; 
 int /*<<< orphan*/ ** port_device ; 

__attribute__((used)) static void hidpad_retrode_deinit(void *data)
{
   struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;

   if (device)
      free(device);

   port_count = 0;
   port_device[0] = NULL;
   port_device[1] = NULL;
   port_device[2] = NULL;
   port_device[3] = NULL;
}