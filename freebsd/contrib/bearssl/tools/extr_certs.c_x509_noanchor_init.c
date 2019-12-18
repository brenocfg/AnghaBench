#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const** inner; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ x509_noanchor_context ;
typedef  int /*<<< orphan*/  br_x509_class ;

/* Variables and functions */
 int /*<<< orphan*/  x509_noanchor_vtable ; 

void
x509_noanchor_init(x509_noanchor_context *xwc, const br_x509_class **inner)
{
	xwc->vtable = &x509_noanchor_vtable;
	xwc->inner = inner;
}