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
struct ihex_data_struct {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {struct ihex_data_struct* ihex_data; } ;
struct TYPE_6__ {TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct ihex_data_struct* bfd_alloc (TYPE_2__*,int) ; 

__attribute__((used)) static bfd_boolean
ihex_mkobject (bfd *abfd)
{
  struct ihex_data_struct *tdata;

  tdata = bfd_alloc (abfd, sizeof (* tdata));
  if (tdata == NULL)
    return FALSE;

  abfd->tdata.ihex_data = tdata;
  tdata->head = NULL;
  tdata->tail = NULL;
  return TRUE;
}