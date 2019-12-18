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
struct TYPE_7__ {unsigned char* h; TYPE_1__ bc; int /*<<< orphan*/  iv; int /*<<< orphan*/  gh; scalar_t__ seq; } ;
typedef  TYPE_2__ br_sslrec_gcm_context ;
typedef  int /*<<< orphan*/  br_ghash ;
struct TYPE_8__ {int /*<<< orphan*/  (* run ) (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,void const*,size_t) ;} ;
typedef  TYPE_3__ br_block_ctr_class ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void
gen_gcm_init(br_sslrec_gcm_context *cc,
	const br_block_ctr_class *bc_impl,
	const void *key, size_t key_len,
	br_ghash gh_impl,
	const void *iv)
{
	unsigned char tmp[12];

	cc->seq = 0;
	bc_impl->init(&cc->bc.vtable, key, key_len);
	cc->gh = gh_impl;
	memcpy(cc->iv, iv, sizeof cc->iv);
	memset(cc->h, 0, sizeof cc->h);
	memset(tmp, 0, sizeof tmp);
	bc_impl->run(&cc->bc.vtable, tmp, 0, cc->h, sizeof cc->h);
}