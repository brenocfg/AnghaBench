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
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int /*<<< orphan*/  assert_int (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * set_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_has (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * set_intersection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * set_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_set() {
    Set *s = NULL;
    assert_int(0, set_has(s, "abc"));
    s = set_add(s, "abc");
    s = set_add(s, "def");
    assert_int(1, set_has(s, "abc"));
    assert_int(1, set_has(s, "def"));
    assert_int(0, set_has(s, "xyz"));
    Set *t = NULL;
    t = set_add(t, "abc");
    t = set_add(t, "DEF");
    assert_int(1, set_has(set_union(s, t), "abc"));
    assert_int(1, set_has(set_union(s, t), "def"));
    assert_int(1, set_has(set_union(s, t), "DEF"));
    assert_int(1, set_has(set_intersection(s, t), "abc"));
    assert_int(0, set_has(set_intersection(s, t), "def"));
    assert_int(0, set_has(set_intersection(s, t), "DEF"));
}