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
 int /*<<< orphan*/  default_globalize_label (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

void
darwin_globalize_label (FILE *stream, const char *name)
{
  if (!!strncmp (name, "_OBJC_", 6))
    default_globalize_label (stream, name);
}