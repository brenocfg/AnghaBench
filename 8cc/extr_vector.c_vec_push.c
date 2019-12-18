#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; void** body; } ;
typedef  TYPE_1__ Vector ;

/* Variables and functions */
 int /*<<< orphan*/  extend (TYPE_1__*,int) ; 

void vec_push(Vector *vec, void *elem) {
    extend(vec, 1);
    vec->body[vec->len++] = elem;
}