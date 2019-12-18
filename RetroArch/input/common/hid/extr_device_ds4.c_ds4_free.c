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
struct TYPE_3__ {int /*<<< orphan*/  pad; } ;
typedef  TYPE_1__ ds4_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hid_pad_deregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds4_free(void *data)
{
   ds4_instance_t *instance = (ds4_instance_t *)data;

   if(instance) {
      hid_pad_deregister(instance->pad);
      free(instance);
   }
}