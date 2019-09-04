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
 int MAXX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dump (unsigned char*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  reset (unsigned char*) ; 

int main() {
  unsigned char buffer[MAXX];
  for (int i = MAXX / 4; i < MAXX - MAXX / 4; i++) {
    for (int j = MAXX / 4; j < MAXX - MAXX / 4; j++) {
      for (int k = 1; k < MAXX / 4; k++) {
        if (i == j) continue;
        if (i < j && i + k > j) continue;
        if (j < i && j + k > i) continue;
        printf("[%d,%d,%d] ", i, j, k);
        reset(buffer);
        memcpy(buffer + i, buffer + j, k);
        dump(buffer);
        assert(memcmp(buffer + i, buffer + j, k) == 0);
        buffer[i + k / 2]++;
        if (buffer[i + k / 2] != 0) {
          assert(memcmp(buffer + i, buffer + j, k) > 0);
        } else {
          assert(memcmp(buffer + i, buffer + j, k) < 0);
        }
        buffer[i + k / 2]--;
        buffer[j + k / 2]++;
        if (buffer[j + k / 2] != 0) {
          assert(memcmp(buffer + i, buffer + j, k) < 0);
        } else {
          assert(memcmp(buffer + i, buffer + j, k) > 0);
        }
      }
    }
  }
  return 0;
}