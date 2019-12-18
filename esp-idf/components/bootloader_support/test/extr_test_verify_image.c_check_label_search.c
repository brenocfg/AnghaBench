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
typedef  int /*<<< orphan*/  label ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_MESSAGE (int,char*) ; 
 int bootloader_common_label_search (char const*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void check_label_search (int num_test, const char *list, const char *t_label, bool result)
{
    // gen_esp32part.py trims up to 16 characters
    // and the string may not have a null terminal symbol.
    // below is cutting as it does the generator.
    char label[16 + 1] = {0};
    strncpy(label, t_label, sizeof(label) - 1);

    bool ret = bootloader_common_label_search(list, label);
    if (ret != result) {
        printf("%d) %s  |  %s \n", num_test, list, label);
    }
    TEST_ASSERT_MESSAGE(ret == result, "Test failed");
}