#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * out; } ;
struct TYPE_6__ {TYPE_1__ vtable; } ;
typedef  TYPE_2__ br_sslrec_chapol_context ;
typedef  int /*<<< orphan*/  br_poly1305_run ;
typedef  int /*<<< orphan*/  br_chacha20_run ;

/* Variables and functions */
 int /*<<< orphan*/  br_sslrec_out_chapol_vtable ; 
 int /*<<< orphan*/  gen_chapol_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,void const*) ; 

__attribute__((used)) static void
out_chapol_init(br_sslrec_chapol_context *cc,
	br_chacha20_run ichacha, br_poly1305_run ipoly,
	const void *key, const void *iv)
{
	cc->vtable.out = &br_sslrec_out_chapol_vtable;
	gen_chapol_init(cc, ichacha, ipoly, key, iv);
}