#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum bfd_endian { ____Placeholder_bfd_endian } bfd_endian ;

/* Variables and functions */
 int BFD_ENDIAN_UNKNOWN ; 
 int target_byte_order ; 
 scalar_t__ target_byte_order_auto ; 

enum bfd_endian
selected_byte_order (void)
{
  if (target_byte_order_auto)
    return BFD_ENDIAN_UNKNOWN;
  else
    return target_byte_order;
}