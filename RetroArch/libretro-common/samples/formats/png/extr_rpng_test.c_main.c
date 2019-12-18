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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ test_rpng (char const*) ; 

int main(int argc, char *argv[])
{
   const char *in_path = "/tmp/test.png";

   if (argc > 2)
   {
      fprintf(stderr, "Usage: %s <png file>\n", argv[0]);
      return 1;
   }

   if (argc == 2)
      in_path = argv[1];

   fprintf(stderr, "Doing tests...\n");

   if (test_rpng(in_path) != 0)
   {
      fprintf(stderr, "Test failed.\n");
      return -1;
   }

   return 0;
}