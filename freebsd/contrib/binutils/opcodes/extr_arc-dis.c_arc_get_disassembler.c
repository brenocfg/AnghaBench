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
typedef  int /*<<< orphan*/  disassembler_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  build_ARC_extmap (void*) ; 
 int /*<<< orphan*/  decodeInstr ; 

disassembler_ftype
arc_get_disassembler (void *ptr)
{
  if (ptr)
    build_ARC_extmap (ptr);
  return decodeInstr;
}