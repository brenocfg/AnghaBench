#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct generic_write_global_symbol_info {int /*<<< orphan*/  psymalloc; int /*<<< orphan*/  output_bfd; TYPE_3__* info; } ;
struct TYPE_13__ {int /*<<< orphan*/  string; } ;
struct TYPE_10__ {scalar_t__ link; } ;
struct TYPE_11__ {TYPE_1__ i; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_4__ root; TYPE_2__ u; } ;
struct generic_link_hash_entry {TYPE_7__ root; TYPE_5__* sym; scalar_t__ written; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ asymbol ;
struct TYPE_12__ {scalar_t__ strip; int /*<<< orphan*/  keep_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_GLOBAL ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * bfd_hash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_5__* bfd_make_empty_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_add_output_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  set_symbol_from_hash (TYPE_5__*,TYPE_7__*) ; 
 scalar_t__ strip_all ; 
 scalar_t__ strip_some ; 

bfd_boolean
_bfd_generic_link_write_global_symbol (struct generic_link_hash_entry *h,
				       void *data)
{
  struct generic_write_global_symbol_info *wginfo = data;
  asymbol *sym;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct generic_link_hash_entry *) h->root.u.i.link;

  if (h->written)
    return TRUE;

  h->written = TRUE;

  if (wginfo->info->strip == strip_all
      || (wginfo->info->strip == strip_some
	  && bfd_hash_lookup (wginfo->info->keep_hash, h->root.root.string,
			      FALSE, FALSE) == NULL))
    return TRUE;

  if (h->sym != NULL)
    sym = h->sym;
  else
    {
      sym = bfd_make_empty_symbol (wginfo->output_bfd);
      if (!sym)
	return FALSE;
      sym->name = h->root.root.string;
      sym->flags = 0;
    }

  set_symbol_from_hash (sym, &h->root);

  sym->flags |= BSF_GLOBAL;

  if (! generic_add_output_symbol (wginfo->output_bfd, wginfo->psymalloc,
				   sym))
    {
      /* FIXME: No way to return failure.  */
      abort ();
    }

  return TRUE;
}