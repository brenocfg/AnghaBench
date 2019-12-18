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
struct bfd_link_order {int type; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  abort () ; 
#define  bfd_data_link_order 132 
#define  bfd_indirect_link_order 131 
#define  bfd_section_reloc_link_order 130 
#define  bfd_symbol_reloc_link_order 129 
#define  bfd_undefined_link_order 128 
 int /*<<< orphan*/  default_data_link_order (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,struct bfd_link_order*) ; 
 int /*<<< orphan*/  default_indirect_link_order (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,struct bfd_link_order*,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_default_link_order (bfd *abfd,
			 struct bfd_link_info *info,
			 asection *sec,
			 struct bfd_link_order *link_order)
{
  switch (link_order->type)
    {
    case bfd_undefined_link_order:
    case bfd_section_reloc_link_order:
    case bfd_symbol_reloc_link_order:
    default:
      abort ();
    case bfd_indirect_link_order:
      return default_indirect_link_order (abfd, info, sec, link_order,
					  FALSE);
    case bfd_data_link_order:
      return default_data_link_order (abfd, info, sec, link_order);
    }
}