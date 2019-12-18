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
struct TYPE_3__ {int* k; int* c; int* d; } ;
typedef  TYPE_1__ key_set ;

/* Variables and functions */
 int /*<<< orphan*/  print_char_as_binary (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_key_set(key_set key_set) {
  int i;
  printf("K: \n");
  for (i = 0; i < 8; i++) {
    printf("%02X : ", key_set.k[i]);
    print_char_as_binary(key_set.k[i]);
    printf("\n");
  }
  printf("\nC: \n");

  for (i = 0; i < 4; i++) {
    printf("%02X : ", key_set.c[i]);
    print_char_as_binary(key_set.c[i]);
    printf("\n");
  }
  printf("\nD: \n");

  for (i = 0; i < 4; i++) {
    printf("%02X : ", key_set.d[i]);
    print_char_as_binary(key_set.d[i]);
    printf("\n");
  }
  printf("\n");
}