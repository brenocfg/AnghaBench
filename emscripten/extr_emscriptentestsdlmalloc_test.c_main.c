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
 int /*<<< orphan*/  assert (char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main(int ac, char **av)
{
  int NUM = ac > 1 ? atoi(av[1]) : 0;
  int REPS = ac > 2 ? atoi(av[2]) : 0;
  int c1 = 0, c2 = 0;
  for (int x = 0; x < REPS; x++) {
    char* allocations[NUM];
    for (int i = 0; i < NUM/2; i++) {
      allocations[i] = (char*)malloc((11*i)%1024 + x);
      //printf("zz alloc: %d\n", (int)allocations[i]);
      assert(allocations[i]);
      if (i > 10 && i%4 == 1 && allocations[i-10]) {
        //printf("zz free: %d\n", (int)allocations[i-10]);
        free(allocations[i-10]);
        allocations[i-10] = NULL;
      }
    }
    for (int i = NUM/2; i < NUM; i++) {
      allocations[i] = (char*)malloc(1024*(i+1));
      //printf("zz alloc: %d\n", (int)allocations[i]);
      assert(allocations[i]);
      if (i > 10 && i%4 != 1 && allocations[i-10]) {
        //printf("zz free: %d\n", (int)allocations[i-10]);
        free(allocations[i-10]);
        allocations[i-10] = NULL;
      }
    }
    char* first = allocations[0];
    for (int i = 0; i < NUM; i++) {
      if (allocations[i]) {
        //printf("zz free: %d\n", (int)allocations[i]);
        free(allocations[i]);
      }
    }
    char *last = (char*)malloc(512); // should be identical, as we free'd it all
    //printf("zz last: %d\n", (int)last);
    char *newer = (char*)malloc(512); // should be different
    //printf("zz newer: %d\n", (int)newer);
#ifndef __APPLE__
    c1 += first == last;
    c2 += first == newer;
#else // On OSX, it's been detected that memory is not necessarily allocated linearly, so skip this check and simulate success.
    ++c1;
#endif
  }
  printf("*%d,%d*\n", c1, c2);
}