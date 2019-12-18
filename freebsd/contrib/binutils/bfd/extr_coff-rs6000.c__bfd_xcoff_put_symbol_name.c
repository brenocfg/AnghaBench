#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ _n_offset; scalar_t__ _n_zeroes; } ;
struct TYPE_6__ {TYPE_1__ _n_n; int /*<<< orphan*/  _n_name; } ;
struct internal_syment {TYPE_2__ _n; } ;
struct bfd_strtab_hash {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_3__ bfd ;

/* Variables and functions */
 int BFD_TRADITIONAL_FORMAT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STRING_SIZE_SIZE ; 
 scalar_t__ SYMNMLEN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _bfd_stringtab_add (struct bfd_strtab_hash*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
_bfd_xcoff_put_symbol_name (bfd *abfd, struct bfd_strtab_hash *strtab,
			    struct internal_syment *sym,
			    const char *name)
{
  if (strlen (name) <= SYMNMLEN)
    {
      strncpy (sym->_n._n_name, name, SYMNMLEN);
    }
  else
    {
      bfd_boolean hash;
      bfd_size_type indx;

      hash = TRUE;
      if ((abfd->flags & BFD_TRADITIONAL_FORMAT) != 0)
	hash = FALSE;
      indx = _bfd_stringtab_add (strtab, name, hash, FALSE);
      if (indx == (bfd_size_type) -1)
	return FALSE;
      sym->_n._n_n._n_zeroes = 0;
      sym->_n._n_n._n_offset = STRING_SIZE_SIZE + indx;
    }
  return TRUE;
}