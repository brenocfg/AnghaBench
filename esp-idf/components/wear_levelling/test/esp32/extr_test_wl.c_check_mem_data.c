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
typedef  int /*<<< orphan*/  wl_handle_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int TEST_SECTORS_COUNT ; 
 int /*<<< orphan*/  wl_read (int /*<<< orphan*/ ,size_t,scalar_t__*,size_t) ; 
 size_t wl_sector_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_mem_data(wl_handle_t handle, uint32_t init_val, uint32_t* buff)
{
    size_t sector_size = wl_sector_size(handle);

    for (int m=0 ; m < TEST_SECTORS_COUNT ; m++) {
        TEST_ESP_OK(wl_read(handle, sector_size * m, buff, sector_size));
        for (int i=0 ; i< sector_size/sizeof(uint32_t) ; i++) {
            uint32_t compare_val = init_val + i +  m*sector_size;
            TEST_ASSERT_EQUAL( buff[i], compare_val);
        }
    }
}