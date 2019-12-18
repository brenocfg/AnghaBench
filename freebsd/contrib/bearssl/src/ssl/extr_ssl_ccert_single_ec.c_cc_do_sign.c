#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t (* iecdsa ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ;int /*<<< orphan*/  sk; int /*<<< orphan*/  iec; int /*<<< orphan*/  mhash; } ;
typedef  TYPE_1__ br_ssl_client_certificate_ec_context ;
typedef  int /*<<< orphan*/  br_ssl_client_certificate_class ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/ * br_multihash_getimpl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static size_t
cc_do_sign(const br_ssl_client_certificate_class **pctx,
	int hash_id, size_t hv_len, unsigned char *data, size_t len)
{
	br_ssl_client_certificate_ec_context *zc;
	unsigned char hv[64];
	const br_hash_class *hc;

	zc = (br_ssl_client_certificate_ec_context *)pctx;
	memcpy(hv, data, hv_len);
	hc = br_multihash_getimpl(zc->mhash, hash_id);
	if (hc == NULL) {
		return 0;
	}
	if (len < 139) {
		return 0;
	}
	return zc->iecdsa(zc->iec, hc, hv, zc->sk, data);
}