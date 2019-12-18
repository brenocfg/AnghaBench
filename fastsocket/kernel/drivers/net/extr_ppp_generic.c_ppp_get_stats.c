#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct slcompress {int /*<<< orphan*/  sls_i_compressed; int /*<<< orphan*/  sls_i_uncompressed; int /*<<< orphan*/  sls_i_tossed; int /*<<< orphan*/  sls_i_error; int /*<<< orphan*/  sls_o_misses; int /*<<< orphan*/  sls_o_searches; scalar_t__ sls_o_compressed; scalar_t__ sls_o_uncompressed; } ;
struct TYPE_8__ {int /*<<< orphan*/  vjs_compressedin; int /*<<< orphan*/  vjs_uncompressedin; int /*<<< orphan*/  vjs_tossed; int /*<<< orphan*/  vjs_errorin; int /*<<< orphan*/  vjs_misses; int /*<<< orphan*/  vjs_searches; scalar_t__ vjs_compressed; scalar_t__ vjs_packets; } ;
struct TYPE_5__ {int /*<<< orphan*/  ppp_obytes; int /*<<< orphan*/  ppp_oerrors; int /*<<< orphan*/  ppp_opackets; int /*<<< orphan*/  ppp_ibytes; int /*<<< orphan*/  ppp_ierrors; int /*<<< orphan*/  ppp_ipackets; } ;
struct ppp_stats {TYPE_4__ vj; TYPE_1__ p; } ;
struct ppp {TYPE_3__* dev; struct slcompress* vj; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_7__ {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ppp_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ppp_get_stats(struct ppp *ppp, struct ppp_stats *st)
{
	struct slcompress *vj = ppp->vj;

	memset(st, 0, sizeof(*st));
	st->p.ppp_ipackets = ppp->dev->stats.rx_packets;
	st->p.ppp_ierrors = ppp->dev->stats.rx_errors;
	st->p.ppp_ibytes = ppp->dev->stats.rx_bytes;
	st->p.ppp_opackets = ppp->dev->stats.tx_packets;
	st->p.ppp_oerrors = ppp->dev->stats.tx_errors;
	st->p.ppp_obytes = ppp->dev->stats.tx_bytes;
	if (!vj)
		return;
	st->vj.vjs_packets = vj->sls_o_compressed + vj->sls_o_uncompressed;
	st->vj.vjs_compressed = vj->sls_o_compressed;
	st->vj.vjs_searches = vj->sls_o_searches;
	st->vj.vjs_misses = vj->sls_o_misses;
	st->vj.vjs_errorin = vj->sls_i_error;
	st->vj.vjs_tossed = vj->sls_i_tossed;
	st->vj.vjs_uncompressedin = vj->sls_i_uncompressed;
	st->vj.vjs_compressedin = vj->sls_i_compressed;
}