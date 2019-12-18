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
struct TYPE_2__ {unsigned int usages; int /*<<< orphan*/  const pkey; } ;
typedef  TYPE_1__ br_x509_knownkey_context ;
typedef  int /*<<< orphan*/  br_x509_class ;

/* Variables and functions */

__attribute__((used)) static const br_x509_pkey *
kk_get_pkey(const br_x509_class *const *ctx, unsigned *usages)
{
	const br_x509_knownkey_context *xc;

	xc = (const br_x509_knownkey_context *)ctx;
	if (usages != NULL) {
		*usages = xc->usages;
	}
	return &xc->pkey;
}