#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* me_record; void* trailer_part; } ;
struct TYPE_13__ {TYPE_1__ r; } ;
struct TYPE_14__ {TYPE_2__ w; } ;
typedef  TYPE_3__ ieee_data_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_15__ {scalar_t__ start_address; } ;
typedef  TYPE_4__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* IEEE_DATA (TYPE_4__*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* bfd_tell (TYPE_4__*) ; 
 int /*<<< orphan*/  ieee_function_either_close_b_enum ; 
 int /*<<< orphan*/  ieee_function_either_open_b_enum ; 
 int /*<<< orphan*/  ieee_module_end_enum ; 
 int /*<<< orphan*/  ieee_value_starting_address_enum ; 
 int /*<<< orphan*/  ieee_write_2bytes (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_byte (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_int (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
ieee_write_me_part (bfd *abfd)
{
  ieee_data_type *ieee = IEEE_DATA (abfd);
  ieee->w.r.trailer_part = bfd_tell (abfd);
  if (abfd->start_address)
    {
      if (! ieee_write_2bytes (abfd, ieee_value_starting_address_enum)
	  || ! ieee_write_byte (abfd, ieee_function_either_open_b_enum)
	  || ! ieee_write_int (abfd, abfd->start_address)
	  || ! ieee_write_byte (abfd, ieee_function_either_close_b_enum))
	return FALSE;
    }
  ieee->w.r.me_record = bfd_tell (abfd);
  if (! ieee_write_byte (abfd, ieee_module_end_enum))
    return FALSE;
  return TRUE;
}