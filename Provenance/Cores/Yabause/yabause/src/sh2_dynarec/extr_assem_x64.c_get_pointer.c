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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ pointer ;

/* Variables and functions */

pointer get_pointer(void *stub)
{
  pointer i_ptr=*((u32 *)(stub+6));
  return *((s32 *)i_ptr)+i_ptr+4;
}