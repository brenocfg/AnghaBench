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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_sleep (int) ; 

__attribute__((used)) static void check_timer(void)
{
   uint32_t start = vcos_getmicrosecs();
   uint32_t sleep_time = 1000;

   printf("0\n");

   while (1)
   {
      uint32_t now;
      vcos_sleep(sleep_time);
      now = vcos_getmicrosecs();
      printf("%d - sleep %d\n", now - start, sleep_time);
   }
}