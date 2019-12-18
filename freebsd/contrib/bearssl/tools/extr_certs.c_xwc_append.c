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
typedef  int /*<<< orphan*/  br_x509_class ;
struct TYPE_4__ {int /*<<< orphan*/  (* append ) (TYPE_2__**,unsigned char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__**,unsigned char const*,size_t) ; 

__attribute__((used)) static void
xwc_append(const br_x509_class **ctx, const unsigned char *buf, size_t len)
{
	x509_noanchor_context *xwc;

	xwc = (x509_noanchor_context *)ctx;
	(*xwc->inner)->append(xwc->inner, buf, len);
}