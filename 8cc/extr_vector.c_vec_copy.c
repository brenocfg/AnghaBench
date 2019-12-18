#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; int /*<<< orphan*/  body; } ;
typedef  TYPE_1__ Vector ;

/* Variables and functions */
 TYPE_1__* do_make_vector (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

Vector *vec_copy(Vector *src) {
    Vector *r = do_make_vector(src->len);
    memcpy(r->body, src->body, sizeof(void *) * src->len);
    r->len = src->len;
    return r;
}