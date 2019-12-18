#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int called; int /*<<< orphan*/  match_path; } ;
typedef  TYPE_1__ dummy_vfs_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static DIR* dummy_opendir(void* ctx, const char* path)
{
    dummy_vfs_t* dummy = (dummy_vfs_t*) ctx;
    dummy->called = true;
    if (strcmp(dummy->match_path, path) == 0) {
        DIR* result = calloc(1, sizeof(DIR));
        TEST_ASSERT_NOT_NULL(result);
        return result;
    }
    errno = ENOENT;
    return NULL;
}