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
typedef  int /*<<< orphan*/  ieee_data_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {int /*<<< orphan*/ * ieee_data; } ;
struct TYPE_6__ {TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/ * bfd_zalloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * input_bfd ; 
 int /*<<< orphan*/ * input_ptr ; 
 int /*<<< orphan*/ * input_ptr_end ; 
 int /*<<< orphan*/ * input_ptr_start ; 
 int /*<<< orphan*/ * output_bfd ; 
 scalar_t__ output_buffer ; 
 int /*<<< orphan*/ * output_ptr ; 
 int /*<<< orphan*/ * output_ptr_end ; 
 int /*<<< orphan*/ * output_ptr_start ; 

__attribute__((used)) static bfd_boolean
ieee_mkobject (bfd *abfd)
{
  bfd_size_type amt;

  output_ptr_start = NULL;
  output_ptr = NULL;
  output_ptr_end = NULL;
  input_ptr_start = NULL;
  input_ptr = NULL;
  input_ptr_end = NULL;
  input_bfd = NULL;
  output_bfd = NULL;
  output_buffer = 0;
  amt = sizeof (ieee_data_type);
  abfd->tdata.ieee_data = bfd_zalloc (abfd, amt);
  return abfd->tdata.ieee_data != NULL;
}