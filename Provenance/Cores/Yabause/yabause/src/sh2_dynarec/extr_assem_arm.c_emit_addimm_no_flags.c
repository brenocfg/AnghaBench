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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  emit_addimm (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

void emit_addimm_no_flags(u32 imm,unsigned int rt)
{
  emit_addimm(rt,imm,rt);
}