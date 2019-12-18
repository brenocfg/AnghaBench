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
typedef  int /*<<< orphan*/  input_device_driver_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* connected ) (unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* pad_connection_listener ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ *) ; 

void fire_connection_listener(unsigned port, input_device_driver_t *driver)
{
   if (!pad_connection_listener)
      return;

   pad_connection_listener->connected(port, driver);
}