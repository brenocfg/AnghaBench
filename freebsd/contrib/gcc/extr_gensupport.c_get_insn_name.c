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
 char const** insn_name_ptr ; 
 int insn_name_ptr_size ; 

const char *
get_insn_name (int code)
{
  if (code < insn_name_ptr_size)
    return insn_name_ptr[code];
  else
    return NULL;
}