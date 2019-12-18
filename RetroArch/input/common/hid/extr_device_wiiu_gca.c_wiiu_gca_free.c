#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int online; } ;
typedef  TYPE_1__ hid_wiiu_gca_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  wiiu_gca_unregister_pad (TYPE_1__*,int) ; 

__attribute__((used)) static void wiiu_gca_free(void *data)
{
   hid_wiiu_gca_instance_t *instance = (hid_wiiu_gca_instance_t *)data;
   int i;

   if(instance)
   {
      instance->online = false;

      for (i = 0; i < 4; i++)
         wiiu_gca_unregister_pad(instance, i);

      free(instance);
   }
}