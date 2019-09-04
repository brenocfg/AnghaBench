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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

int main()
{
  // i32 vs i64
  int32_t small = -1;
  int64_t large = -1;
  printf("*%d*\n", small == large);
  small++;
  printf("*%d*\n", small == large);
  uint32_t usmall = -1;
  uint64_t ularge = -1;
  printf("*%d*\n", usmall == ularge);
  return 0;
}