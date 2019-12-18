#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ me_record; } ;
struct TYPE_6__ {scalar_t__* offset; TYPE_1__ r; } ;
struct TYPE_7__ {TYPE_2__ w; } ;
typedef  TYPE_3__ ieee_data_type ;
typedef  scalar_t__ file_ptr ;

/* Variables and functions */
 int N_W_VARIABLES ; 

__attribute__((used)) static file_ptr
ieee_part_after (ieee_data_type *ieee, file_ptr here)
{
  int part;
  file_ptr after = ieee->w.r.me_record;

  /* File parts can come in any order, except that module end is
     guaranteed to be last (and the header first).  */
  for (part = 0; part < N_W_VARIABLES; part++)
    if (ieee->w.offset[part] > here && after > ieee->w.offset[part])
      after = ieee->w.offset[part];

  return after;
}