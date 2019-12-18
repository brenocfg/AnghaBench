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
struct TYPE_3__ {int nalloc; scalar_t__ len; void* body; } ;
typedef  TYPE_1__ Buffer ;

/* Variables and functions */
 int INIT_SIZE ; 
 void* malloc (int) ; 

Buffer *make_buffer() {
    Buffer *r = malloc(sizeof(Buffer));
    r->body = malloc(INIT_SIZE);
    r->nalloc = INIT_SIZE;
    r->len = 0;
    return r;
}