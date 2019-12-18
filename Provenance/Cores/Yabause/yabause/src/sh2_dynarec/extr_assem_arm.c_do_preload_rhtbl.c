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
 int /*<<< orphan*/  FP ; 
 int /*<<< orphan*/  dynarec_local ; 
 int /*<<< orphan*/  emit_addimm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mini_ht_master ; 
 int /*<<< orphan*/  mini_ht_slave ; 
 scalar_t__ slave ; 

void do_preload_rhtbl(int ht) {
  if(slave) emit_addimm(FP,(int)&mini_ht_slave-(int)&dynarec_local,ht);
  else emit_addimm(FP,(int)&mini_ht_master-(int)&dynarec_local,ht);
}