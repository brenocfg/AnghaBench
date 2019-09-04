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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

int main(int argc, char *argv[]) {
  uint8_t byte = 0x80;
  uint16_t two = byte;
  uint32_t four = byte;
  uint64_t eight = byte;

  printf("value: %d,%d,%d,%lld.\n", byte, two, four, eight);

  return 0;
}