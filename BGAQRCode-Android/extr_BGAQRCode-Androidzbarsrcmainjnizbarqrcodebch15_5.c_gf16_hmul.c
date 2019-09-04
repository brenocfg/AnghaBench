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
 int* gf16_exp ; 
 unsigned int* gf16_log ; 

__attribute__((used)) static unsigned gf16_hmul(unsigned _a,unsigned _logb){
  return _a==0?0:gf16_exp[gf16_log[_a]+_logb];
}