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
 int /*<<< orphan*/  FOPEN_WB ; 
 int /*<<< orphan*/  dump_value_to_file (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dump_ihex_value (char *args, int from_tty)
{
  dump_value_to_file (args, FOPEN_WB, "ihex");
}