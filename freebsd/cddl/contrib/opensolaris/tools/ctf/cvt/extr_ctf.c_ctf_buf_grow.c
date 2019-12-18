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
typedef  scalar_t__ off_t ;
struct TYPE_3__ {scalar_t__ ctb_base; scalar_t__ ctb_ptr; scalar_t__ ctb_size; scalar_t__ ctb_end; } ;
typedef  TYPE_1__ ctf_buf_t ;

/* Variables and functions */
 scalar_t__ CTF_BUF_CHUNK_SIZE ; 
 scalar_t__ xrealloc (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ctf_buf_grow(ctf_buf_t *b)
{
	off_t ptroff = b->ctb_ptr - b->ctb_base;

	b->ctb_size += CTF_BUF_CHUNK_SIZE;
	b->ctb_base = xrealloc(b->ctb_base, b->ctb_size);
	b->ctb_end = b->ctb_base + b->ctb_size;
	b->ctb_ptr = b->ctb_base + ptroff;
}