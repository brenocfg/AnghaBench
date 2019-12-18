#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct srec_symbol {char const* name; struct srec_symbol* next; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {TYPE_1__* srec_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  symcount; TYPE_2__ tdata; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_6__ {struct srec_symbol* symtail; struct srec_symbol* symbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct srec_symbol* bfd_alloc (TYPE_3__*,int) ; 

__attribute__((used)) static bfd_boolean
srec_new_symbol (bfd *abfd, const char *name, bfd_vma val)
{
  struct srec_symbol *n;

  n = bfd_alloc (abfd, sizeof (* n));
  if (n == NULL)
    return FALSE;

  n->name = name;
  n->val = val;

  if (abfd->tdata.srec_data->symbols == NULL)
    abfd->tdata.srec_data->symbols = n;
  else
    abfd->tdata.srec_data->symtail->next = n;
  abfd->tdata.srec_data->symtail = n;
  n->next = NULL;

  ++abfd->symcount;

  return TRUE;
}