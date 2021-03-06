#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_2__* sk; TYPE_1__* iec; } ;
typedef  TYPE_3__ br_ssl_client_certificate_ec_context ;
typedef  int /*<<< orphan*/  br_ssl_client_certificate_class ;
struct TYPE_5__ {int /*<<< orphan*/  curve; int /*<<< orphan*/  xlen; int /*<<< orphan*/  x; } ;
struct TYPE_4__ {size_t (* xoff ) (int /*<<< orphan*/ ,size_t*) ;int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub2 (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static uint32_t
cc_do_keyx(const br_ssl_client_certificate_class **pctx,
	unsigned char *data, size_t *len)
{
	br_ssl_client_certificate_ec_context *zc;
	uint32_t r;
	size_t xoff, xlen;

	zc = (br_ssl_client_certificate_ec_context *)pctx;
	r = zc->iec->mul(data, *len, zc->sk->x, zc->sk->xlen, zc->sk->curve);
	xoff = zc->iec->xoff(zc->sk->curve, &xlen);
	memmove(data, data + xoff, xlen);
	*len = xlen;
	return r;
}