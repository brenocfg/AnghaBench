#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__** inner; } ;
typedef  TYPE_1__ x509_noanchor_context ;
typedef  int /*<<< orphan*/  br_x509_pkey ;
typedef  int /*<<< orphan*/  br_x509_class ;
struct TYPE_4__ {int /*<<< orphan*/  const* (* get_pkey ) (TYPE_2__**,unsigned int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  const* stub1 (TYPE_2__**,unsigned int*) ; 

__attribute__((used)) static const br_x509_pkey *
xwc_get_pkey(const br_x509_class *const *ctx, unsigned *usages)
{
	x509_noanchor_context *xwc;

	xwc = (x509_noanchor_context *)ctx;
	return (*xwc->inner)->get_pkey(xwc->inner, usages);
}