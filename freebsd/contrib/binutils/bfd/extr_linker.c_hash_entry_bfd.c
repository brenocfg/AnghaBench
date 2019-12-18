#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_8__* p; } ;
struct TYPE_12__ {TYPE_3__* section; } ;
struct TYPE_10__ {int /*<<< orphan*/ * abfd; } ;
struct TYPE_9__ {struct bfd_link_hash_entry* link; } ;
struct TYPE_13__ {TYPE_7__ c; TYPE_4__ def; TYPE_2__ undef; TYPE_1__ i; } ;
struct bfd_link_hash_entry {int type; TYPE_5__ u; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {TYPE_6__* section; } ;
struct TYPE_14__ {int /*<<< orphan*/ * owner; } ;
struct TYPE_11__ {int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
#define  bfd_link_hash_common 132 
#define  bfd_link_hash_defined 131 
#define  bfd_link_hash_defweak 130 
#define  bfd_link_hash_undefined 129 
#define  bfd_link_hash_undefweak 128 
 int bfd_link_hash_warning ; 

__attribute__((used)) static bfd *
hash_entry_bfd (struct bfd_link_hash_entry *h)
{
  while (h->type == bfd_link_hash_warning)
    h = h->u.i.link;
  switch (h->type)
    {
    default:
      return NULL;
    case bfd_link_hash_undefined:
    case bfd_link_hash_undefweak:
      return h->u.undef.abfd;
    case bfd_link_hash_defined:
    case bfd_link_hash_defweak:
      return h->u.def.section->owner;
    case bfd_link_hash_common:
      return h->u.c.p->section->owner;
    }
  /*NOTREACHED*/
}