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
 char const** backslashed ; 
 char const* represented ; 
 char* strchr (char const*,int) ; 
 int /*<<< orphan*/  target_char_to_host (int,int*) ; 

__attribute__((used)) static const char *
default_c_target_char_has_backslash_escape (void *baton, int target_char)
{
  int host_char;
  const char *ix;

  /* If target_char has no equivalent in the host character set,
     assume it doesn't have a backslashed form.  */
  if (! target_char_to_host (target_char, &host_char))
    return NULL;

  ix = strchr (represented, host_char);
  if (ix)
    return backslashed[ix - represented];
  else
    return NULL;
}