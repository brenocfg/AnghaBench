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
struct bfd_link_order {struct bfd_link_order* next; int /*<<< orphan*/  type; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {struct bfd_link_order* link_order; } ;
struct TYPE_5__ {struct bfd_link_order* link_order; } ;
struct TYPE_7__ {TYPE_2__ map_tail; TYPE_1__ map_head; } ;
typedef  TYPE_3__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_undefined_link_order ; 
 struct bfd_link_order* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

struct bfd_link_order *
bfd_new_link_order (bfd *abfd, asection *section)
{
  bfd_size_type amt = sizeof (struct bfd_link_order);
  struct bfd_link_order *new;

  new = bfd_zalloc (abfd, amt);
  if (!new)
    return NULL;

  new->type = bfd_undefined_link_order;

  if (section->map_tail.link_order != NULL)
    section->map_tail.link_order->next = new;
  else
    section->map_head.link_order = new;
  section->map_tail.link_order = new;

  return new;
}