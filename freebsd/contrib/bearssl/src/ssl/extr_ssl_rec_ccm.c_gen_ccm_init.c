#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_7__ {size_t tag_len; int /*<<< orphan*/  iv; TYPE_1__ bc; scalar_t__ seq; } ;
typedef  TYPE_2__ br_sslrec_ccm_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,void const*,size_t) ;} ;
typedef  TYPE_3__ br_block_ctrcbc_class ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
gen_ccm_init(br_sslrec_ccm_context *cc,
	const br_block_ctrcbc_class *bc_impl,
	const void *key, size_t key_len,
	const void *iv, size_t tag_len)
{
	cc->seq = 0;
	bc_impl->init(&cc->bc.vtable, key, key_len);
	memcpy(cc->iv, iv, sizeof cc->iv);
	cc->tag_len = tag_len;
}