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
typedef  int di_int ;

/* Variables and functions */
 int __divdi3 (int,int) ; 

di_int __divmoddi4(di_int a, di_int b, di_int *rem) {
  di_int d = __divdi3(a, b);
  *rem = a - (d * b);
  return d;
}