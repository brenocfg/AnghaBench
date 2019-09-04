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
struct TYPE_3__ {unsigned int* log; int* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */

__attribute__((used)) static unsigned rs_gsqrt(const rs_gf256 *_gf,unsigned _a){
  unsigned loga;
  if(!_a)return 0;
  loga=_gf->log[_a];
  return _gf->exp[loga+(255&-(loga&1))>>1];
}