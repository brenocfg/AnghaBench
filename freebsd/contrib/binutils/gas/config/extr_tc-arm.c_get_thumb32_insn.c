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

/* Variables and functions */
 int THUMB_SIZE ; 
 unsigned long md_chars_to_number (char*,int) ; 

__attribute__((used)) static unsigned long
get_thumb32_insn (char * buf)
{
  unsigned long insn;
  insn = md_chars_to_number (buf, THUMB_SIZE) << 16;
  insn |= md_chars_to_number (buf + THUMB_SIZE, THUMB_SIZE);

  return insn;
}