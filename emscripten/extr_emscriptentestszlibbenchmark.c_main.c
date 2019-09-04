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
 int /*<<< orphan*/  doit (unsigned char*,int,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char **argv) {
  int size, iters;
  int arg = argc > 1 ? argv[1][0] - '0' : 3;
  switch(arg) {
    case 0: return 0; break;
    case 1: size = 100000; iters = 60; break;
    case 2: size = 100000; iters = 250; break;
    case 3: size = 100000; iters = 500; break;
    case 4: size = 100000; iters = 5*500; break;
    case 5: size = 100000; iters = 10*500; break;
    default: printf("error: %d\\n", arg); return -1;
  }

  unsigned char *buffer = (unsigned char*)malloc(size);

  int i = 0;
  int run = 0;
  char runChar = 17;
  while (i < size) {
    if (run > 0) {
      run--;
    } else {
      if ((i & 7) == 0) {
        runChar = i & 7;
        run = i & 31;
      } else {
        runChar = (i*i) % 6714;
      }
    }
    buffer[i] = runChar;
    i++;
  }

  for (i = 0; i < iters; i++) {
    doit(buffer, size, i);
  }

  printf("ok.\n");

  return 0;
}