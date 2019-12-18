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
struct stab_write_handle {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_LSYM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_tag (void *p, const char *tag)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  char *s, *buf;

  s = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (tag) + strlen (s) + 3);

  sprintf (buf, "%s:T%s", tag, s);
  free (s);

  if (! stab_write_symbol (info, N_LSYM, 0, 0, buf))
    return FALSE;

  free (buf);

  return TRUE;
}