#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  enc; } ;
typedef  TYPE_1__ symmetric_xts ;
struct ccmode_xts {int /*<<< orphan*/  (* xts ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_tweak ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  tweak_size; } ;
struct TYPE_5__ {struct ccmode_xts* ccaes_xts_encrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccxts_tweak_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_crypto_funcs ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tweak ; 

int xts_encrypt(const uint8_t *pt, unsigned long ptlen,
			uint8_t *ct,
			const uint8_t *iv, // this can be considered the sector IV for this use
			symmetric_xts *xts)
{
	const struct ccmode_xts *xtsenc = g_crypto_funcs->ccaes_xts_encrypt;
	ccxts_tweak_decl(xtsenc->tweak_size, tweak);
		
	if(ptlen%16) panic("xts encrypt not a multiple of block size\n");

	xtsenc->set_tweak(xts->enc, tweak, iv);
	xtsenc->xts(xts->enc, tweak, ptlen/16, pt, ct);
	
	return 0; //never fails
}