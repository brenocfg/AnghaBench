#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * the_bfd; scalar_t__ section; } ;
struct TYPE_5__ {TYPE_2__ symbol; int /*<<< orphan*/  done_lineno; int /*<<< orphan*/ * lineno; scalar_t__ native; } ;
typedef  TYPE_1__ coff_symbol_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  TYPE_2__ asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

asymbol *
coff_make_empty_symbol (bfd *abfd)
{
  bfd_size_type amt = sizeof (coff_symbol_type);
  coff_symbol_type *new = bfd_zalloc (abfd, amt);

  if (new == NULL)
    return NULL;
  new->symbol.section = 0;
  new->native = 0;
  new->lineno = NULL;
  new->done_lineno = FALSE;
  new->symbol.the_bfd = abfd;

  return & new->symbol;
}