#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; int /*<<< orphan*/ * csymbols; int /*<<< orphan*/ * symtail; int /*<<< orphan*/ * symbols; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
typedef  TYPE_2__ tdata_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {TYPE_2__* srec_data; } ;
struct TYPE_9__ {TYPE_1__ tdata; } ;
typedef  TYPE_3__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* bfd_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  srec_init () ; 

__attribute__((used)) static bfd_boolean
srec_mkobject (bfd *abfd)
{
  tdata_type *tdata;

  srec_init ();

  tdata = bfd_alloc (abfd, sizeof (tdata_type));
  if (tdata == NULL)
    return FALSE;

  abfd->tdata.srec_data = tdata;
  tdata->type = 1;
  tdata->head = NULL;
  tdata->tail = NULL;
  tdata->symbols = NULL;
  tdata->symtail = NULL;
  tdata->csymbols = NULL;

  return TRUE;
}