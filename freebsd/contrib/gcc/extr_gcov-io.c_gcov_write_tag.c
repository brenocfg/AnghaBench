#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gcov_unsigned_t ;
typedef  scalar_t__ gcov_position_t ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ start; } ;

/* Variables and functions */
 TYPE_1__ gcov_var ; 
 scalar_t__* gcov_write_words (int) ; 

gcov_position_t
gcov_write_tag (gcov_unsigned_t tag)
{
  gcov_position_t result = gcov_var.start + gcov_var.offset;
  gcov_unsigned_t *buffer = gcov_write_words (2);

  buffer[0] = tag;
  buffer[1] = 0;
  
  return result;
}