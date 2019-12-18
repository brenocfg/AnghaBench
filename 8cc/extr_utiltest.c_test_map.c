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
 int /*<<< orphan*/  assert_int (int,intptr_t) ; 
 int /*<<< orphan*/  assert_null (scalar_t__) ; 
 char* format (char*,int) ; 
 int /*<<< orphan*/ * make_map () ; 
 scalar_t__ map_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  map_remove (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_map() {
    Map *m = make_map();
    assert_null(map_get(m, "abc"));

    // Insert 10000 values
    for (int i = 0; i < 10000; i++) {
        char *k = format("%d", i);
        map_put(m, k, (void *)(intptr_t)i);
        assert_int(i, (int)(intptr_t)map_get(m, k));
    }

    // Insert again
    for (int i = 0; i < 1000; i++) {
        char *k = format("%d", i);
        map_put(m, k, (void *)(intptr_t)i);
        assert_int(i, (int)(intptr_t)map_get(m, k));
    }

    // Remove them
    for (int i = 0; i < 10000; i++) {
        char *k = format("%d", i);
        assert_int(i, (intptr_t)map_get(m, k));
        map_remove(m, k);
        assert_null(map_get(m, k));
    }
}