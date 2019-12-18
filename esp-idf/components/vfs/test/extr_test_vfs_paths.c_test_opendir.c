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
struct TYPE_3__ {int called; } ;
typedef  TYPE_1__ dummy_vfs_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_TEST_ASSERT (int,int,char*) ; 
 int /*<<< orphan*/  UNITY_TEST_ASSERT_EQUAL_INT (int,int,int,char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 

__attribute__((used)) static void test_opendir(dummy_vfs_t* instance, const char* path,
        bool should_be_called, bool should_be_opened, int line)
{
    instance->called = false;
    DIR* dir = opendir(path);
    UNITY_TEST_ASSERT_EQUAL_INT(should_be_called, instance->called, line,
            "should_be_called check failed");
    if (should_be_called) {
        if (should_be_opened) {
            UNITY_TEST_ASSERT(dir != NULL, line, "should be opened");
        } else {
            UNITY_TEST_ASSERT(dir == 0, line, "should not be opened");
        }
    }
    if (dir) {
        closedir(dir);
    }
}