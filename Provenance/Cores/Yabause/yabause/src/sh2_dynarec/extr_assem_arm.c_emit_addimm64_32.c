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
 int /*<<< orphan*/  HOST_TEMPREG ; 
 int /*<<< orphan*/  emit_adcimm (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_adds (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_movimm (int,int /*<<< orphan*/ ) ; 

void emit_addimm64_32(int rsh,int rsl,int imm,int rth,int rtl)
{
  // TODO: if(genimm(imm,&armval)) ...
  // else
  emit_movimm(imm,HOST_TEMPREG);
  emit_adds(HOST_TEMPREG,rsl,rtl);
  emit_adcimm(rsh,0,rth);
}