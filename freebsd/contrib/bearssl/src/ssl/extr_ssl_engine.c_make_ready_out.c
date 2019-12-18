#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* vtable; } ;
struct TYPE_6__ {size_t obuf_len; size_t max_frag_len; size_t oxa; size_t oxb; size_t oxc; scalar_t__ iomode; TYPE_1__ out; } ;
typedef  TYPE_2__ br_ssl_engine_context ;
struct TYPE_7__ {int /*<<< orphan*/  (* max_plaintext ) (TYPE_3__**,size_t*,size_t*) ;} ;

/* Variables and functions */
 scalar_t__ BR_IO_INOUT ; 
 scalar_t__ BR_IO_OUT ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,size_t*,size_t*) ; 

__attribute__((used)) static void
make_ready_out(br_ssl_engine_context *rc)
{
	size_t a, b;

	a = 5;
	b = rc->obuf_len - a;
	rc->out.vtable->max_plaintext(&rc->out.vtable, &a, &b);
	if ((b - a) > rc->max_frag_len) {
		b = a + rc->max_frag_len;
	}
	rc->oxa = a;
	rc->oxb = b;
	rc->oxc = a;
	if (rc->iomode == BR_IO_OUT) {
		rc->iomode = BR_IO_INOUT;
	}
}