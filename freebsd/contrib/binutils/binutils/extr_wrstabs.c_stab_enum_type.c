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
struct stab_write_handle {long type_index; } ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_LSYM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  stab_push_defined_type (struct stab_write_handle*,long,int) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ xmalloc (size_t) ; 

__attribute__((used)) static bfd_boolean
stab_enum_type (void *p, const char *tag, const char **names,
		bfd_signed_vma *vals)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  size_t len;
  const char **pn;
  char *buf;
  long index = 0;
  bfd_signed_vma *pv;

  if (names == NULL)
    {
      assert (tag != NULL);

      buf = (char *) xmalloc (10 + strlen (tag));
      sprintf (buf, "xe%s:", tag);
      /* FIXME: The size is just a guess.  */
      if (! stab_push_string (info, buf, 0, FALSE, 4))
	return FALSE;
      free (buf);
      return TRUE;
    }

  len = 10;
  if (tag != NULL)
    len += strlen (tag);
  for (pn = names; *pn != NULL; pn++)
    len += strlen (*pn) + 20;

  buf = (char *) xmalloc (len);

  if (tag == NULL)
    strcpy (buf, "e");
  else
    {
      index = info->type_index;
      ++info->type_index;
      sprintf (buf, "%s:T%ld=e", tag, index);
    }

  for (pn = names, pv = vals; *pn != NULL; pn++, pv++)
    sprintf (buf + strlen (buf), "%s:%ld,", *pn, (long) *pv);
  strcat (buf, ";");

  if (tag == NULL)
    {
      /* FIXME: The size is just a guess.  */
      if (! stab_push_string (info, buf, 0, FALSE, 4))
	return FALSE;
    }
  else
    {
      /* FIXME: The size is just a guess.  */
      if (! stab_write_symbol (info, N_LSYM, 0, 0, buf)
	  || ! stab_push_defined_type (info, index, 4))
	return FALSE;
    }

  free (buf);

  return TRUE;
}