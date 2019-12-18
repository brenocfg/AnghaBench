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
struct bfd_symbol {int dummy; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct bfd_symbol** _bfd_generic_link_get_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_generic_link_get_symcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_link_add_symbol_list (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ,struct bfd_symbol**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_link_read_symbols (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
generic_link_add_object_symbols (bfd *abfd,
				 struct bfd_link_info *info,
				 bfd_boolean collect)
{
  bfd_size_type symcount;
  struct bfd_symbol **outsyms;

  if (! generic_link_read_symbols (abfd))
    return FALSE;
  symcount = _bfd_generic_link_get_symcount (abfd);
  outsyms = _bfd_generic_link_get_symbols (abfd);
  return generic_link_add_symbol_list (abfd, info, symcount, outsyms, collect);
}