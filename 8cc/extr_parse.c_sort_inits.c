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
 int /*<<< orphan*/  comp_init ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sort_inits(Vector *inits) {
    qsort(vec_body(inits), vec_len(inits), sizeof(void *), comp_init);
}