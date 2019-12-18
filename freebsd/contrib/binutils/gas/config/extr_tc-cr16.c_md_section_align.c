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
typedef  int valueT ;
typedef  scalar_t__ segT ;

/* Variables and functions */
 scalar_t__ text_section ; 

valueT
md_section_align (segT seg, valueT val)
{
  /* Round .text section to a multiple of 2.  */
  if (seg == text_section)
    return (val + 1) & ~1;
  return val;
}