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
struct TYPE_6__ {int /*<<< orphan*/ * the_bfd; } ;
struct TYPE_5__ {TYPE_2__ symbol; int /*<<< orphan*/ * prev; } ;
typedef  TYPE_1__ tekhex_symbol_type ;
struct tekhex_symbol_struct {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  TYPE_2__ asymbol ;

/* Variables and functions */
 TYPE_1__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static asymbol *
tekhex_make_empty_symbol (bfd *abfd)
{
  bfd_size_type amt = sizeof (struct tekhex_symbol_struct);
  tekhex_symbol_type *new = bfd_zalloc (abfd, amt);

  if (!new)
    return NULL;
  new->symbol.the_bfd = abfd;
  new->prev =  NULL;
  return &(new->symbol);
}