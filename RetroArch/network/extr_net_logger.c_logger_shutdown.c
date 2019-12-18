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
 int /*<<< orphan*/  g_sid ; 
 int /*<<< orphan*/  network_deinit () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ socket_close (int /*<<< orphan*/ ) ; 

void logger_shutdown (void)
{
   if (socket_close(g_sid) < 0)
      printf("Could not close socket.\n");

   network_deinit();
}