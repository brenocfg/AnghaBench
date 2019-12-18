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
 int /*<<< orphan*/  XCS (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int is_whitespace_normalized (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
testhelper_is_whitespace_normalized(void)
{
    assert(is_whitespace_normalized(XCS("abc"), 0));
    assert(is_whitespace_normalized(XCS("abc"), 1));
    assert(is_whitespace_normalized(XCS("abc def ghi"), 0));
    assert(is_whitespace_normalized(XCS("abc def ghi"), 1));
    assert(!is_whitespace_normalized(XCS(" abc def ghi"), 0));
    assert(is_whitespace_normalized(XCS(" abc def ghi"), 1));
    assert(!is_whitespace_normalized(XCS("abc  def ghi"), 0));
    assert(is_whitespace_normalized(XCS("abc  def ghi"), 1));
    assert(!is_whitespace_normalized(XCS("abc def ghi "), 0));
    assert(is_whitespace_normalized(XCS("abc def ghi "), 1));
    assert(!is_whitespace_normalized(XCS(" "), 0));
    assert(is_whitespace_normalized(XCS(" "), 1));
    assert(!is_whitespace_normalized(XCS("\t"), 0));
    assert(!is_whitespace_normalized(XCS("\t"), 1));
    assert(!is_whitespace_normalized(XCS("\n"), 0));
    assert(!is_whitespace_normalized(XCS("\n"), 1));
    assert(!is_whitespace_normalized(XCS("\r"), 0));
    assert(!is_whitespace_normalized(XCS("\r"), 1));
    assert(!is_whitespace_normalized(XCS("abc\t def"), 1));
}