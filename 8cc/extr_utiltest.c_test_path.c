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
 int /*<<< orphan*/  assert_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullpath (char*) ; 

__attribute__((used)) static void test_path() {
    assert_string("/abc", fullpath("/abc"));
    assert_string("/abc/def", fullpath("/abc/def"));
    assert_string("/abc/def", fullpath("/abc///def"));
    assert_string("/abc/def", fullpath("//abc///def"));
    assert_string("/abc/xyz", fullpath("/abc/def/../xyz"));
    assert_string("/xyz", fullpath("/abc/def/../../../xyz"));
    assert_string("/xyz", fullpath("/abc/def/../../../../xyz"));
}