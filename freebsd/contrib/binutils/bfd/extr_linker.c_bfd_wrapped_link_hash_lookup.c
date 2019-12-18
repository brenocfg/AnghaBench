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
struct bfd_link_info {char const wrap_char; int /*<<< orphan*/  hash; int /*<<< orphan*/ * wrap_hash; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REAL ; 
 int /*<<< orphan*/  TRUE ; 
 char const* WRAP ; 
 char const bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* bfd_malloc (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct bfd_link_hash_entry *
bfd_wrapped_link_hash_lookup (bfd *abfd,
			      struct bfd_link_info *info,
			      const char *string,
			      bfd_boolean create,
			      bfd_boolean copy,
			      bfd_boolean follow)
{
  bfd_size_type amt;

  if (info->wrap_hash != NULL)
    {
      const char *l;
      char prefix = '\0';

      l = string;
      if (*l == bfd_get_symbol_leading_char (abfd) || *l == info->wrap_char)
	{
	  prefix = *l;
	  ++l;
	}

#undef WRAP
#define WRAP "__wrap_"

      if (bfd_hash_lookup (info->wrap_hash, l, FALSE, FALSE) != NULL)
	{
	  char *n;
	  struct bfd_link_hash_entry *h;

	  /* This symbol is being wrapped.  We want to replace all
             references to SYM with references to __wrap_SYM.  */

	  amt = strlen (l) + sizeof WRAP + 1;
	  n = bfd_malloc (amt);
	  if (n == NULL)
	    return NULL;

	  n[0] = prefix;
	  n[1] = '\0';
	  strcat (n, WRAP);
	  strcat (n, l);
	  h = bfd_link_hash_lookup (info->hash, n, create, TRUE, follow);
	  free (n);
	  return h;
	}

#undef WRAP

#undef  REAL
#define REAL "__real_"

      if (*l == '_'
	  && CONST_STRNEQ (l, REAL)
	  && bfd_hash_lookup (info->wrap_hash, l + sizeof REAL - 1,
			      FALSE, FALSE) != NULL)
	{
	  char *n;
	  struct bfd_link_hash_entry *h;

	  /* This is a reference to __real_SYM, where SYM is being
             wrapped.  We want to replace all references to __real_SYM
             with references to SYM.  */

	  amt = strlen (l + sizeof REAL - 1) + 2;
	  n = bfd_malloc (amt);
	  if (n == NULL)
	    return NULL;

	  n[0] = prefix;
	  n[1] = '\0';
	  strcat (n, l + sizeof REAL - 1);
	  h = bfd_link_hash_lookup (info->hash, n, create, TRUE, follow);
	  free (n);
	  return h;
	}

#undef REAL
    }

  return bfd_link_hash_lookup (info->hash, string, create, copy, follow);
}