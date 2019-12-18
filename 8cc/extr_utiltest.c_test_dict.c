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
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 int /*<<< orphan*/  assert_int (int,long) ; 
 int /*<<< orphan*/  assert_null (scalar_t__) ; 
 scalar_t__ dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dict_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dict_put (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/ * make_dict () ; 
 long vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_dict() {
    Dict *dict = make_dict();
    assert_null(dict_get(dict, "abc"));
    dict_put(dict, "abc", (void *)50);
    dict_put(dict, "xyz", (void *)70);
    assert_int(50, (long)dict_get(dict, "abc"));
    assert_int(70, (long)dict_get(dict, "xyz"));
    assert_int(2, vec_len(dict_keys(dict)));
}