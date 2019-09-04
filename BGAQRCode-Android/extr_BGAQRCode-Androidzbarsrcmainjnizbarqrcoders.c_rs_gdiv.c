#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* exp; size_t* log; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */

__attribute__((used)) static unsigned rs_gdiv(const rs_gf256 *_gf,unsigned _a,unsigned _b){
  return _a==0?0:_gf->exp[_gf->log[_a]+255-_gf->log[_b]];
}