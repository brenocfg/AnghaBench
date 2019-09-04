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
 int* cache ; 
 int* next ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main() {
  cache[10] = 25;
  next[20] = 51;
  printf("*%d,%d*\n", next[10], cache[20]);
  return 0;
}