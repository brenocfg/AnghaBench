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
struct charset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*) ; 
 struct charset* lookup_charset (char const*) ; 

__attribute__((used)) static struct charset *
lookup_charset_or_error (const char *name)
{
  struct charset *cs = lookup_charset (name);

  if (! cs)
    error ("GDB doesn't know of any character set named `%s'.", name);

  return cs;
}