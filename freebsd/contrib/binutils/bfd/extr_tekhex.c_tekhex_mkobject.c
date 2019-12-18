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
struct TYPE_8__ {int type; int /*<<< orphan*/ * data; int /*<<< orphan*/ * symbols; int /*<<< orphan*/ * head; } ;
typedef  TYPE_2__ tdata_type ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {TYPE_2__* tekhex_data; } ;
struct TYPE_9__ {TYPE_1__ tdata; } ;
typedef  TYPE_3__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* bfd_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
tekhex_mkobject (bfd *abfd)
{
  tdata_type *tdata;

  tdata = bfd_alloc (abfd, (bfd_size_type) sizeof (tdata_type));
  if (!tdata)
    return FALSE;
  abfd->tdata.tekhex_data = tdata;
  tdata->type = 1;
  tdata->head =  NULL;
  tdata->symbols = NULL;
  tdata->data = NULL;
  return TRUE;
}