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
struct hidpad_nesusb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct hidpad_nesusb_data*) ; 

__attribute__((used)) static void hidpad_nesusb_deinit(void *data)
{
   struct hidpad_nesusb_data *device = (struct hidpad_nesusb_data*)data;

   if (device)
      free(device);
}