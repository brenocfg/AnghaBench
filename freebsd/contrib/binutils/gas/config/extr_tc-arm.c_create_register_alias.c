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
struct reg_entry {int /*<<< orphan*/  type; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 char TOLOWER (char) ; 
 char TOUPPER (char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  arm_reg_hsh ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*) ; 
 struct reg_entry* hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  insert_reg_alias (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* original_case_string ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

__attribute__((used)) static int
create_register_alias (char * newname, char *p)
{
  struct reg_entry *old;
  char *oldname, *nbuf;
  size_t nlen;

  /* The input scrubber ensures that whitespace after the mnemonic is
     collapsed to single spaces.  */
  oldname = p;
  if (strncmp (oldname, " .req ", 6) != 0)
    return 0;

  oldname += 6;
  if (*oldname == '\0')
    return 0;

  old = hash_find (arm_reg_hsh, oldname);
  if (!old)
    {
      as_warn (_("unknown register '%s' -- .req ignored"), oldname);
      return 1;
    }

  /* If TC_CASE_SENSITIVE is defined, then newname already points to
     the desired alias name, and p points to its end.  If not, then
     the desired alias name is in the global original_case_string.  */
#ifdef TC_CASE_SENSITIVE
  nlen = p - newname;
#else
  newname = original_case_string;
  nlen = strlen (newname);
#endif

  nbuf = alloca (nlen + 1);
  memcpy (nbuf, newname, nlen);
  nbuf[nlen] = '\0';

  /* Create aliases under the new name as stated; an all-lowercase
     version of the new name; and an all-uppercase version of the new
     name.  */
  insert_reg_alias (nbuf, old->number, old->type);

  for (p = nbuf; *p; p++)
    *p = TOUPPER (*p);

  if (strncmp (nbuf, newname, nlen))
    insert_reg_alias (nbuf, old->number, old->type);

  for (p = nbuf; *p; p++)
    *p = TOLOWER (*p);

  if (strncmp (nbuf, newname, nlen))
    insert_reg_alias (nbuf, old->number, old->type);

  return 1;
}