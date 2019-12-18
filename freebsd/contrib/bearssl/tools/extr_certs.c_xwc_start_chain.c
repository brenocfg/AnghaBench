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
struct TYPE_4__ {int /*<<< orphan*/  (* start_chain ) (TYPE_2__**,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__**,char const*) ; 

__attribute__((used)) static void
xwc_start_chain(const br_x509_class **ctx, const char *server_name)
{
	x509_noanchor_context *xwc;

	xwc = (x509_noanchor_context *)ctx;
	(*xwc->inner)->start_chain(xwc->inner, server_name);
}