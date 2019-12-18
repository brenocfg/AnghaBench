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
struct TYPE_5__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_6__ {TYPE_1__ key; int /*<<< orphan*/  key_type; } ;
struct TYPE_7__ {unsigned int usages; TYPE_2__ pkey; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_3__ br_x509_knownkey_context ;
typedef  int /*<<< orphan*/  br_rsa_public_key ;

/* Variables and functions */
 int /*<<< orphan*/  BR_KEYTYPE_RSA ; 
 int /*<<< orphan*/  br_x509_knownkey_vtable ; 

void
br_x509_knownkey_init_rsa(br_x509_knownkey_context *ctx,
	const br_rsa_public_key *pk, unsigned usages)
{
	ctx->vtable = &br_x509_knownkey_vtable;
	ctx->pkey.key_type = BR_KEYTYPE_RSA;
	ctx->pkey.key.rsa = *pk;
	ctx->usages = usages;
}