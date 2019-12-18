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
 int CHAR_BIT ; 
 int /*<<< orphan*/  compilerrt_abort () ; 

di_int __negvdi2(di_int a) {
  const di_int MIN = (di_int)1 << ((int)(sizeof(di_int) * CHAR_BIT) - 1);
  if (a == MIN)
    compilerrt_abort();
  return -a;
}