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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t esp_himem_get_free_size () ; 
 size_t esp_himem_get_phys_size () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  test_region (size_t,int) ; 

void app_main(void)
{
    size_t memcnt=esp_himem_get_phys_size();
    size_t memfree=esp_himem_get_free_size();
    printf("Himem has %dKiB of memory, %dKiB of which is free. Testing the free memory...\n", (int)memcnt/1024, (int)memfree/1024);
    assert(test_region(memfree, 0xaaaa));
    printf("Done!\n");
}