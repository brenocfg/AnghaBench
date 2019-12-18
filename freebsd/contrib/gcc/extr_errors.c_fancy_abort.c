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
 int /*<<< orphan*/  internal_error (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trim_filename (char const*) ; 

void
fancy_abort (const char *file, int line, const char *func)
{
  internal_error ("abort in %s, at %s:%d", func, trim_filename (file), line);
}