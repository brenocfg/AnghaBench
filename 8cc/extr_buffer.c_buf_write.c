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
struct TYPE_4__ {scalar_t__ nalloc; scalar_t__ len; char* body; } ;
typedef  TYPE_1__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  realloc_body (TYPE_1__*) ; 

void buf_write(Buffer *b, char c) {
    if (b->nalloc == (b->len + 1))
        realloc_body(b);
    b->body[b->len++] = c;
}