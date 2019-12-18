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
struct connect_wii_wiimote_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct connect_wii_wiimote_t*) ; 

__attribute__((used)) static void hidpad_wii_deinit(void *data)
{
   struct connect_wii_wiimote_t* device = (struct connect_wii_wiimote_t*)data;

   if (device)
      free(device);
}