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
typedef  int /*<<< orphan*/  ecoff_data_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {int /*<<< orphan*/ * ecoff_obj_data; } ;
struct TYPE_6__ {TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_zalloc (TYPE_2__*,int) ; 

bfd_boolean
_bfd_ecoff_mkobject (bfd *abfd)
{
  bfd_size_type amt = sizeof (ecoff_data_type);

  abfd->tdata.ecoff_obj_data = bfd_zalloc (abfd, amt);
  if (abfd->tdata.ecoff_obj_data == NULL)
    return FALSE;

  return TRUE;
}