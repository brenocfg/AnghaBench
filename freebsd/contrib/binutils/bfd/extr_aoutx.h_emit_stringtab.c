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
struct bfd_strtab_hash {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int BYTES_IN_WORD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PUT_WORD (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_stringtab_emit (int /*<<< orphan*/ *,struct bfd_strtab_hash*) ; 
 int _bfd_stringtab_size (struct bfd_strtab_hash*) ; 
 scalar_t__ bfd_bwrite (void*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
emit_stringtab (bfd *abfd, struct bfd_strtab_hash *tab)
{
  bfd_byte buffer[BYTES_IN_WORD];
  bfd_size_type amt = BYTES_IN_WORD;

  /* The string table starts with the size.  */
  PUT_WORD (abfd, _bfd_stringtab_size (tab) + BYTES_IN_WORD, buffer);
  if (bfd_bwrite ((void *) buffer, amt, abfd) != amt)
    return FALSE;

  return _bfd_stringtab_emit (abfd, tab);
}