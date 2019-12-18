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
typedef  int /*<<< orphan*/  br_x509_pkey ;
struct TYPE_2__ {scalar_t__ err; unsigned int key_usages; int /*<<< orphan*/  const pkey; } ;
typedef  TYPE_1__ br_x509_minimal_context ;
typedef  int /*<<< orphan*/  br_x509_class ;

/* Variables and functions */
 scalar_t__ BR_ERR_X509_NOT_TRUSTED ; 
 scalar_t__ BR_ERR_X509_OK ; 

__attribute__((used)) static const br_x509_pkey *
xm_get_pkey(const br_x509_class *const *ctx, unsigned *usages)
{
	br_x509_minimal_context *cc;

	cc = (br_x509_minimal_context *)(void *)ctx;
	if (cc->err == BR_ERR_X509_OK
		|| cc->err == BR_ERR_X509_NOT_TRUSTED)
	{
		if (usages != NULL) {
			*usages = cc->key_usages;
		}
		return &((br_x509_minimal_context *)(void *)ctx)->pkey;
	} else {
		return NULL;
	}
}