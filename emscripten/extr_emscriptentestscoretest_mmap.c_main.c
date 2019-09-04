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
 int MAP_ANON ; 
 int* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int getpagesize () ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int const,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (int*,int const) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int main(int argc, char* argv[]) {
  // Alignment check for mmap below should be consistent with the reported page size
  // For now, just require it to be 16384
  assert(getpagesize() == 16384);
  assert(sysconf(_SC_PAGESIZE) == 16384);

  for (int i = 0; i < 10; i++) {
    int* map = (int*)mmap(0, 5000, PROT_READ | PROT_WRITE,
                          MAP_SHARED | MAP_ANON, -1, 0);
    assert(map != MAP_FAILED);
    assert(((int)map) % 16384 == 0); // aligned
    assert(munmap(map, 5000) == 0);
  }

  const int NUM_BYTES = 8 * 1024 * 1024;
  const int NUM_INTS = NUM_BYTES / sizeof(int);

  int* map = (int*)mmap(0, NUM_BYTES, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANON, -1, 0);
  assert(map != MAP_FAILED);

  int i;

  for (i = 0; i < NUM_INTS; i++) {
    map[i] = i;
  }

  for (i = 0; i < NUM_INTS; i++) {
    assert(map[i] == i);
  }

  assert(munmap(map, NUM_BYTES) == 0);

  printf("hello,world");
  return 0;
}