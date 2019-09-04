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
typedef  int volatile UINT64 ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int volatile) ; 

int main() {
  volatile UINT32 testu32a = 2375724032U;
  UINT32 bigu32 = 0xffffffffU;
  volatile UINT64 testu64a = 14746250828952703000U;

  while ((UINT64)testu32a * (UINT64)bigu32 < testu64a) {
    printf("testu64a is %llu\n", testu64a);
    testu64a /= 2;
  }

  return 0;
}