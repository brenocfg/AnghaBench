#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {TYPE_2__* symbol; TYPE_2__** symbol_ptr_ptr; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;
struct TYPE_5__ {int /*<<< orphan*/  flags; TYPE_1__* section; scalar_t__ value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_SECTION_SYM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_generic_new_section_hook (bfd *abfd, asection *newsect)
{
  newsect->symbol = bfd_make_empty_symbol (abfd);
  if (newsect->symbol == NULL)
    return FALSE;

  newsect->symbol->name = newsect->name;
  newsect->symbol->value = 0;
  newsect->symbol->section = newsect;
  newsect->symbol->flags = BSF_SECTION_SYM;

  newsect->symbol_ptr_ptr = &newsect->symbol;
  return TRUE;
}