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
typedef  int /*<<< orphan*/  Vector ;

/* Variables and functions */
 int /*<<< orphan*/  KHASHHASH ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_head (int /*<<< orphan*/ *) ; 
 scalar_t__ vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_tail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hashhash_check(Vector *v) {
    if (vec_len(v) == 0)
        return;
    if (is_keyword(vec_head(v), KHASHHASH))
        errort(vec_head(v), "'##' cannot appear at start of macro expansion");
    if (is_keyword(vec_tail(v), KHASHHASH))
        errort(vec_tail(v), "'##' cannot appear at end of macro expansion");
}