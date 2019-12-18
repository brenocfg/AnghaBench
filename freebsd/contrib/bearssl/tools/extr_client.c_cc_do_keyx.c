#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_3__* sk; } ;
typedef  TYPE_4__ ccert_context ;
typedef  int /*<<< orphan*/  br_ssl_client_certificate_class ;
struct TYPE_11__ {size_t (* xoff ) (int /*<<< orphan*/ ,size_t*) ;int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ br_ec_impl ;
struct TYPE_7__ {int /*<<< orphan*/  curve; int /*<<< orphan*/  xlen; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_1__ ec; } ;
struct TYPE_9__ {TYPE_2__ key; } ;

/* Variables and functions */
 TYPE_5__* br_ec_get_default () ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub2 (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static uint32_t
cc_do_keyx(const br_ssl_client_certificate_class **pctx,
	unsigned char *data, size_t *len)
{
	const br_ec_impl *iec;
	ccert_context *zc;
	size_t xoff, xlen;
	uint32_t r;

	zc = (ccert_context *)pctx;
	iec = br_ec_get_default();
	r = iec->mul(data, *len, zc->sk->key.ec.x,
		zc->sk->key.ec.xlen, zc->sk->key.ec.curve);
	xoff = iec->xoff(zc->sk->key.ec.curve, &xlen);
	memmove(data, data + xoff, xlen);
	*len = xlen;
	return r;
}