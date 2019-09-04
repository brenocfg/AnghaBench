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
typedef  int /*<<< orphan*/ * voidStar ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int get_TOTAL_MEMORY () ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 void* sbrk (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
  int totalMemory = get_TOTAL_MEMORY();
  int chunk = 1024*1024;
  volatile voidStar alloc;
  for (int i = 0; i < (totalMemory/chunk)+2; i++) {
    // make sure state remains the same if malloc fails
    void* sbrk_before = sbrk(0);
    alloc = malloc(chunk);
    printf("%d : %d\n", i, !!alloc);
    if (alloc == NULL) {
      assert(sbrk(0) == sbrk_before);
      assert(totalMemory == get_TOTAL_MEMORY());
      break;
    }
  }
  assert(alloc == NULL);
  puts("ok.");
  return 0;
}