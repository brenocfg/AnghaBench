#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; void** body; } ;
typedef  TYPE_1__ Vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void vec_set(Vector *vec, int index, void *val) {
    assert(0 <= index && index < vec->len);
    vec->body[index] = val;
}