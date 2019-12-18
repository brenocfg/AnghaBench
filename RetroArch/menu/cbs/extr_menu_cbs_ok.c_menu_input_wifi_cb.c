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

/* Variables and functions */
 int /*<<< orphan*/  driver_wifi_connect_ssid (unsigned int,char const*) ; 
 int /*<<< orphan*/  menu_input_dialog_end () ; 
 unsigned int menu_input_dialog_get_kb_idx () ; 

__attribute__((used)) static void menu_input_wifi_cb(void *userdata, const char *passphrase)
{
   unsigned idx = menu_input_dialog_get_kb_idx();

   driver_wifi_connect_ssid(idx, passphrase);

   menu_input_dialog_end();
}