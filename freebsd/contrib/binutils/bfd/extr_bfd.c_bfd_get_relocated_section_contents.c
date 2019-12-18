#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* section; } ;
struct TYPE_12__ {TYPE_3__ indirect; } ;
struct bfd_link_order {scalar_t__ type; TYPE_4__ u; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_13__ {TYPE_1__* xvec; } ;
typedef  TYPE_5__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_10__ {TYPE_5__* owner; } ;
struct TYPE_9__ {int /*<<< orphan*/ * (* _bfd_get_relocated_section_contents ) (TYPE_5__*,struct bfd_link_info*,struct bfd_link_order*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 scalar_t__ bfd_indirect_link_order ; 
 int /*<<< orphan*/ * stub1 (TYPE_5__*,struct bfd_link_info*,struct bfd_link_order*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

bfd_byte *
bfd_get_relocated_section_contents (bfd *abfd,
				    struct bfd_link_info *link_info,
				    struct bfd_link_order *link_order,
				    bfd_byte *data,
				    bfd_boolean relocatable,
				    asymbol **symbols)
{
  bfd *abfd2;
  bfd_byte *(*fn) (bfd *, struct bfd_link_info *, struct bfd_link_order *,
		   bfd_byte *, bfd_boolean, asymbol **);

  if (link_order->type == bfd_indirect_link_order)
    {
      abfd2 = link_order->u.indirect.section->owner;
      if (abfd2 == NULL)
	abfd2 = abfd;
    }
  else
    abfd2 = abfd;

  fn = abfd2->xvec->_bfd_get_relocated_section_contents;

  return (*fn) (abfd, link_info, link_order, data, relocatable, symbols);
}