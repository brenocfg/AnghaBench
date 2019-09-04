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
 int /*<<< orphan*/  game (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int main(int argc, char **argv)
{
  int w, h, i;
  int arg = argc > 1 ? argv[1][0] - '0' : 3;
  switch(arg) {
    case 0: return 0; break;
    case 1: w = h = 32; i = 2500; break;
    case 2: w = h = 32; i = 13000; break;
    case 3: w = h = 32; i = 24000; break;
    case 4: w = h = 32; i = 5*24000; break;
    case 5: w = h = 32; i = 10*24000; break;
    default: printf("error: %d\\n", arg); return -1;
  }

  printf("life: %d,%d,%d,%d\n", arg, w, h, i);
  game(w, h, i);

  return 0;
}