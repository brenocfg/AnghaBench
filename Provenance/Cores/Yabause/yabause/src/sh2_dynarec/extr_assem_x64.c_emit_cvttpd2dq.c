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
 int /*<<< orphan*/  assem_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,unsigned int,unsigned int) ; 

void emit_cvttpd2dq(unsigned int ssereg1,unsigned int ssereg2)
{
  assem_debug("cvttpd2dq xmm%d,xmm%d\n",ssereg1,ssereg2);
  assert(ssereg1<8);
  assert(ssereg2<8);
  output_byte(0x66);
  output_byte(0x0f);
  output_byte(0xe6);
  output_modrm(3,ssereg1,ssereg2);
}