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
struct TYPE_5__ {int len; int body; } ;
typedef  TYPE_1__ Vector ;

/* Variables and functions */
 int /*<<< orphan*/  extend (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int,int,int) ; 

void vec_append(Vector *a, Vector *b) {
    extend(a, b->len);
    memcpy(a->body + a->len, b->body, sizeof(void *) * b->len);
    a->len += b->len;
}