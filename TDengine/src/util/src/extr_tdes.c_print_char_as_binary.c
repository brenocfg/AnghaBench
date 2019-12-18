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
 int /*<<< orphan*/  printf (char*) ; 

void print_char_as_binary(char input) {
  int i;
  for (i = 0; i < 8; i++) {
    char shift_byte = 0x01 << (7 - i);
    if (shift_byte & input) {
      printf("1");
    } else {
      printf("0");
    }
  }
}