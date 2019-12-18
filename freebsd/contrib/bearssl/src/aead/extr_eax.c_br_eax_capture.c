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
struct TYPE_6__ {unsigned char* st; } ;
typedef  TYPE_1__ br_eax_state ;
struct TYPE_7__ {TYPE_3__** bctx; } ;
typedef  TYPE_2__ br_eax_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* mac ) (TYPE_3__**,unsigned char,unsigned char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,unsigned char,unsigned char*,int) ; 

void
br_eax_capture(const br_eax_context *ctx, br_eax_state *st)
{
	/*
	 * We capture the three OMAC* states _after_ processing the
	 * initial block (assuming that nonce, message and AAD are
	 * all non-empty).
	 */
	int i;

	memset(st->st, 0, sizeof st->st);
	for (i = 0; i < 3; i ++) {
		unsigned char tmp[16];

		memset(tmp, 0, sizeof tmp);
		tmp[15] = (unsigned char)i;
		(*ctx->bctx)->mac(ctx->bctx, st->st[i], tmp, sizeof tmp);
	}
}