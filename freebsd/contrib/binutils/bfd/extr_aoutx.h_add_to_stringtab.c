#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfd_strtab_hash {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int BFD_TRADITIONAL_FORMAT ; 
 scalar_t__ BYTES_IN_WORD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _bfd_stringtab_add (struct bfd_strtab_hash*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bfd_size_type
add_to_stringtab (bfd *abfd,
		  struct bfd_strtab_hash *tab,
		  const char *str,
		  bfd_boolean copy)
{
  bfd_boolean hash;
  bfd_size_type index;

  /* An index of 0 always means the empty string.  */
  if (str == 0 || *str == '\0')
    return 0;

  /* Don't hash if BFD_TRADITIONAL_FORMAT is set, because SunOS dbx
     doesn't understand a hashed string table.  */
  hash = TRUE;
  if ((abfd->flags & BFD_TRADITIONAL_FORMAT) != 0)
    hash = FALSE;

  index = _bfd_stringtab_add (tab, str, hash, copy);

  if (index != (bfd_size_type) -1)
    /* Add BYTES_IN_WORD to the return value to account for the
       space taken up by the string table size.  */
    index += BYTES_IN_WORD;

  return index;
}