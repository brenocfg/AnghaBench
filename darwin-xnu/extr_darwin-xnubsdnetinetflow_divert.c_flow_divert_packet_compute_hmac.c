#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct flow_divert_group {int /*<<< orphan*/ * token_key; int /*<<< orphan*/  token_key_size; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
struct TYPE_2__ {int /*<<< orphan*/  ccsha1_di; int /*<<< orphan*/  (* cchmac_final_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cchmac_update_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cchmac_init_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  cchmac_di_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_crypto_funcs ; 
 int /*<<< orphan*/  hmac_ctx ; 
 int /*<<< orphan*/  mbuf_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flow_divert_packet_compute_hmac(mbuf_t packet, struct flow_divert_group *group, uint8_t *hmac)
{
	mbuf_t	curr_mbuf	= packet;

	if (g_crypto_funcs == NULL || group->token_key == NULL) {
		return ENOPROTOOPT;
	}

	cchmac_di_decl(g_crypto_funcs->ccsha1_di, hmac_ctx);
	g_crypto_funcs->cchmac_init_fn(g_crypto_funcs->ccsha1_di, hmac_ctx, group->token_key_size, group->token_key);

	while (curr_mbuf != NULL) {
		g_crypto_funcs->cchmac_update_fn(g_crypto_funcs->ccsha1_di, hmac_ctx, mbuf_len(curr_mbuf), mbuf_data(curr_mbuf));
		curr_mbuf = mbuf_next(curr_mbuf);
	}

	g_crypto_funcs->cchmac_final_fn(g_crypto_funcs->ccsha1_di, hmac_ctx, hmac);

	return 0;
}