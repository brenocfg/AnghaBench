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
struct TYPE_6__ {size_t oxa; size_t oxb; size_t oxc; unsigned char* obuf; int /*<<< orphan*/  version_out; int /*<<< orphan*/  record_type_out; TYPE_1__ out; } ;
typedef  TYPE_2__ br_ssl_engine_context ;
struct TYPE_7__ {unsigned char* (* encrypt ) (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t*) ;} ;

/* Variables and functions */
 unsigned char* stub1 (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t*) ; 

__attribute__((used)) static void
sendpld_flush(br_ssl_engine_context *rc, int force)
{
	size_t xlen;
	unsigned char *buf;

	if (rc->oxa == rc->oxb) {
		return;
	}
	xlen = rc->oxa - rc->oxc;
	if (xlen == 0 && !force) {
		return;
	}
	buf = rc->out.vtable->encrypt(&rc->out.vtable,
		rc->record_type_out, rc->version_out,
		rc->obuf + rc->oxc, &xlen);
	rc->oxb = rc->oxa = (size_t)(buf - rc->obuf);
	rc->oxc = rc->oxa + xlen;
}