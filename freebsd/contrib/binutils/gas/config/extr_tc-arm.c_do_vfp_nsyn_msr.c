#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* operands; } ;
struct TYPE_3__ {scalar_t__ isvec; } ;

/* Variables and functions */
 int FAIL ; 
 int SUCCESS ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char*) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static int
do_vfp_nsyn_msr (void)
{
  if (inst.operands[0].isvec)
    do_vfp_nsyn_opcode ("fmxr");
  else
    return FAIL;

  return SUCCESS;
}