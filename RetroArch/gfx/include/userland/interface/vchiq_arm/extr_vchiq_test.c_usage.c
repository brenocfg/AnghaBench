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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
   printf("Usage: vchiq_test [<options>] <mode> <iters>\n");
   printf("  where <options> is any of:\n");
   printf("    -a <c> <s>  set the client and server bulk alignment (modulo 32)\n");
   printf("    -A <c> <s>  set the client and server bulk alignment (modulo 4096)\n");
   printf("    -e          disable echoing in the main bulk transfer mode\n");
   printf("    -k <n>      skip the first <n> func data tests\n");
   printf("    -m <n>      set the client message quota to <n>\n");
   printf("    -M <n>      set the server message quota to <n>\n");
   printf("    -q          disable data verification\n");
   printf("    -s ????     service (any 4 characters)\n");
   printf("    -v          enable more verbose output\n");
   printf("    -r <b> <s>  reserve <b> bytes for <s> seconds\n");
   printf("    -K <t>      send a SIGKILL after <t> ms\n");
   printf("  and <mode> is one of:\n");
   printf("    -c <size>   control test (size in bytes)\n");
   printf("    -b <size>   bulk test (size in kilobytes)\n");
   printf("    -f          functional test\n");
   printf("    -p          ping test\n");
   printf("    -t          check the timer\n");
   printf("  and <iters> is the number of test iterations\n");
   exit(1);
}