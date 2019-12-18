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
 int /*<<< orphan*/  socketclose (int) ; 
 int wiiu_log_socket ; 

__attribute__((used)) static void wiiu_log_deinit(void)
{
   if(wiiu_log_socket >= 0)
   {
      socketclose(wiiu_log_socket);
      wiiu_log_socket = -1;
   }
}