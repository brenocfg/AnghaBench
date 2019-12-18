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
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 int /*<<< orphan*/  assert_int (int,int) ; 
 int /*<<< orphan*/ * make_map () ; 
 int /*<<< orphan*/ * make_map_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ map_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,char*,void*) ; 

__attribute__((used)) static void test_map_stack() {
    Map *m1 = make_map();
    map_put(m1, "x", (void *)1);
    map_put(m1, "y", (void *)2);
    assert_int(1, (int)(intptr_t)map_get(m1, "x"));

    Map *m2 = make_map_parent(m1);
    assert_int(1, (int)(intptr_t)map_get(m2, "x"));
    map_put(m2, "x", (void *)3);
    assert_int(3, (int)(intptr_t)map_get(m2, "x"));
    assert_int(1, (int)(intptr_t)map_get(m1, "x"));
}