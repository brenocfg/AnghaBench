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
 int /*<<< orphan*/  delete_temp_files () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror_with_name (char const*) ; 

void
pfatal_with_name (const char *name)
{
  perror_with_name (name);
  delete_temp_files ();
  exit (1);
}