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
 int /*<<< orphan*/  emit_adc (int,int) ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_shrimm (int,int,int) ; 

void emit_dt(int t, int sr)
{
  emit_addimm(t,-2,t);
  emit_shrimm(sr,1,sr);
  emit_addimm(t,1,t);
  emit_adc(sr,sr);
}