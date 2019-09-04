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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 char* memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
  char buffer[256];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 35; k++) {
        for (int t = 0; t < 256; t++) buffer[t] = t;
        char *dest = buffer + i + 128;
        char *src = buffer + j;
        // printf("%d, %d, %d\n", i, j, k);
        assert(memcpy(dest, src, k) == dest);
        assert(memcmp(dest, src, k) == 0);
      }
    }
  }
  printf("ok.\n");
  return 1;
}