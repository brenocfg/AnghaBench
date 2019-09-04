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

unsigned bch15_5_encode(unsigned _x){
  return (-(_x&1)&0x0537)^(-(_x>>1&1)&0x0A6E)^(-(_x>>2&1)&0x11EB)^
   (-(_x>>3&1)&0x23D6)^(-(_x>>4&1)&0x429B);
}