#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ address; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 TYPE_1__* get_test_data_partition () ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ start ; 

__attribute__((used)) static void setup_tests(void)
{
    if (start == 0) {
        const esp_partition_t *part = get_test_data_partition();
        start = part->address;
        printf("Test data partition @ 0x%x\n", start);
    }
}