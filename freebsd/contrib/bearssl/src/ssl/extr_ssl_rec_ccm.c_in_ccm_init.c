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
struct TYPE_5__ {int /*<<< orphan*/ * in; } ;
struct TYPE_6__ {TYPE_1__ vtable; } ;
typedef  TYPE_2__ br_sslrec_ccm_context ;
typedef  int /*<<< orphan*/  br_block_ctrcbc_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_sslrec_in_ccm_vtable ; 
 int /*<<< orphan*/  gen_ccm_init (TYPE_2__*,int /*<<< orphan*/  const*,void const*,size_t,void const*,size_t) ; 

__attribute__((used)) static void
in_ccm_init(br_sslrec_ccm_context *cc,
	const br_block_ctrcbc_class *bc_impl,
	const void *key, size_t key_len,
	const void *iv, size_t tag_len)
{
	cc->vtable.in = &br_sslrec_in_ccm_vtable;
	gen_ccm_init(cc, bc_impl, key, key_len, iv, tag_len);
}