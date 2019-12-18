#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  avail_out; int /*<<< orphan*/ * next_out; } ;
struct TYPE_5__ {TYPE_1__ rb_zstr; scalar_t__ rb_ptr; scalar_t__ rb_base; int /*<<< orphan*/  rb_size; } ;
typedef  TYPE_2__ resbuf_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 scalar_t__ RES_BUF_CHUNK_SIZE ; 
 scalar_t__ xrealloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rbzs_grow(resbuf_t *rb)
{
	off_t ptroff = (caddr_t)rb->rb_zstr.next_out - rb->rb_base;

	rb->rb_size += RES_BUF_CHUNK_SIZE;
	rb->rb_base = xrealloc(rb->rb_base, rb->rb_size);
	rb->rb_ptr = rb->rb_base + ptroff;
	rb->rb_zstr.next_out = (Bytef *)(rb->rb_ptr);
	rb->rb_zstr.avail_out += RES_BUF_CHUNK_SIZE;
}