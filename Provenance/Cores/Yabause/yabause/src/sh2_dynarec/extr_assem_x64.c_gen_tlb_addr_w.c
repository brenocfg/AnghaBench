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
 int /*<<< orphan*/  emit_leairrx1 (int /*<<< orphan*/ ,int,int,int) ; 

int gen_tlb_addr_w(int ar, int map) {
  if(map>=0) {
    emit_leairrx1(0,ar,map,ar);
  }
}