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
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int main(int argc, char **argv) {
  printf("argc %d\n", argc);
  char buffer[100];
  for (int i = 0; i < 100; i++) buffer[i] = argc*(argc > 10 ? (argc*i) % 3 : (i*i));
  memset(&buffer[10], -114, argc+25);
  for(int i = 0; i < 100; i++) printf("%d:%d\n", i, buffer[i]);
  //memset 5243040,-114,6,false,6
  return buffer[15];
}