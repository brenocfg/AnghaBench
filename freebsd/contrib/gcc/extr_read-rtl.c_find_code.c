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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GET_RTX_NAME (int) ; 
 int NUM_RTX_CODE ; 
 int /*<<< orphan*/  fatal_with_file_and_line (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
find_code (const char *name, FILE *infile)
{
  int i;

  for (i = 0; i < NUM_RTX_CODE; i++)
    if (strcmp (GET_RTX_NAME (i), name) == 0)
      return i;

  fatal_with_file_and_line (infile, "unknown rtx code `%s'", name);
}