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
 char* obstack_copy0 (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  temporary_obstack ; 

__attribute__((used)) static char *
frob_extension (const char *s, const char *ext)
{
  const char *p = strrchr (s, '/');
  if (! p)
    p = s;
  p = strrchr (p, '.');
  if (! p)
    p = s + strlen (s);

  obstack_grow (&temporary_obstack, s, p - s);
  return obstack_copy0 (&temporary_obstack, ext, strlen (ext));
}