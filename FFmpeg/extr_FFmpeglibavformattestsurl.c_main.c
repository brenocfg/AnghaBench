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
 int /*<<< orphan*/  test (char*,char*) ; 

int main(void)
{
    test(NULL, "baz");
    test("/foo/bar", "baz");
    test("/foo/bar", "../baz");
    test("/foo/bar", "/baz");
    test("http://server/foo/", "baz");
    test("http://server/foo/bar", "baz");
    test("http://server/foo/", "../baz");
    test("http://server/foo/bar/123", "../../baz");
    test("http://server/foo/bar/123", "/baz");
    test("http://server/foo/bar/123", "https://other/url");
    test("http://server/foo/bar?param=value/with/slashes", "/baz");
    test("http://server/foo/bar?param&otherparam", "?someparam");
    test("http://server/foo/bar", "//other/url");
    return 0;
}