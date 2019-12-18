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
struct test {char* name; } ;

/* Variables and functions */
 char* VERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct test* tests ; 

__attribute__((used)) static void usage(const char* name)
{
  printf("%s %s: run a string related benchmark.\n"
         "usage: %s [-c block-size] [-l loop-count] [-a alignment|src_alignment:dst_alignment] [-f] [-t test-name] [-r run-id]\n"
         , name, VERSION, name);

  printf("Tests:");

  for (const struct test *ptest = tests; ptest->name != NULL; ptest++)
    {
      printf(" %s", ptest->name);
    }

  printf("\n");

  exit(-1);
}