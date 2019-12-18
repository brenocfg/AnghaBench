#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; scalar_t__ st_size; } ;
struct TYPE_11__ {scalar_t__ me_record; } ;
struct TYPE_12__ {TYPE_1__ r; } ;
struct TYPE_15__ {TYPE_2__ w; } ;
typedef  TYPE_5__ ieee_data_type ;
typedef  int /*<<< orphan*/  ieee_ar_data_type ;
struct TYPE_16__ {TYPE_4__* my_archive; } ;
typedef  TYPE_6__ bfd ;
struct TYPE_13__ {int /*<<< orphan*/ * ieee_ar_data; } ;
struct TYPE_14__ {TYPE_3__ tdata; } ;

/* Variables and functions */
 TYPE_5__* IEEE_DATA (TYPE_6__*) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee_object_p (TYPE_6__*) ; 

__attribute__((used)) static int
ieee_generic_stat_arch_elt (bfd *abfd, struct stat *buf)
{
  ieee_ar_data_type *ar = (ieee_ar_data_type *) NULL;
  ieee_data_type *ieee;

  if (abfd->my_archive != NULL)
    ar = abfd->my_archive->tdata.ieee_ar_data;
  if (ar == (ieee_ar_data_type *) NULL)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  if (IEEE_DATA (abfd) == NULL)
    {
      if (ieee_object_p (abfd) == NULL)
	{
	  bfd_set_error (bfd_error_wrong_format);
	  return -1;
	}
    }

  ieee = IEEE_DATA (abfd);

  buf->st_size = ieee->w.r.me_record + 1;
  buf->st_mode = 0644;
  return 0;
}