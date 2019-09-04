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
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  freeproxy (void*) ; 
 int /*<<< orphan*/  get_lib () ; 
 int handles ; 
 void* malloc (int) ; 
 void* mallocproxy (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  unget_lib () ; 

int main() {
  int n = 0, total = 0, l = 0;
  void *allocs[50];
  allocs[10] = malloc(10); // pull in real malloc
  for (int i = 0; i < 1000; i++) {
    //printf("%d: total ever %d MB, current MB %d, total libs %d\n", i, total, n, l);
    if (i % 5 == 0) {
      if (handles < 10) {
        get_lib();
        l++;
      }
    }
    if (i % 7 == 0) {
      if (handles > 0) unget_lib();
    }
    if (i % 3 == 0) {
      if (handles > 0) {
        if (n < 10) {
          if (i % 2 == 0) {
            //printf("alloc\n");
            allocs[n++] = mallocproxy(1024*1024);
          } else {
            //printf("real alloc\n");
            allocs[n++] = malloc(1024*1024);
          }
          total++;
        } else {
          //printf("real free\n");
          free(allocs[--n]); // real free
        }
      }
    }
    if (i % 4 == 0) {
      if (handles > 0 && n > 0) {
        //printf("free\n");
        if (i % 2 == 0) {
          //printf("free\n");
          freeproxy(allocs[--n]);
        } else {
          //printf("real free\n");
          free(allocs[--n]);
        }
      }
    }
  }
  while (n > 0) free(allocs[--n]); // real free
  while (handles > 0) unget_lib();
  printf("*%d,%d*\n", total, l);
}