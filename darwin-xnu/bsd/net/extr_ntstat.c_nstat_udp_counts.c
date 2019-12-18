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
struct nstat_tucookie {struct inpcb* inp; } ;
struct nstat_counts {int /*<<< orphan*/  nstat_wired_txbytes; int /*<<< orphan*/  nstat_wired_rxbytes; int /*<<< orphan*/  nstat_wifi_txbytes; int /*<<< orphan*/  nstat_wifi_rxbytes; int /*<<< orphan*/  nstat_cell_txbytes; int /*<<< orphan*/  nstat_cell_rxbytes; int /*<<< orphan*/  nstat_txbytes; int /*<<< orphan*/  nstat_txpackets; int /*<<< orphan*/  nstat_rxbytes; int /*<<< orphan*/  nstat_rxpackets; } ;
struct inpcb {TYPE_4__* inp_Wstat; TYPE_3__* inp_wstat; TYPE_2__* inp_cstat; TYPE_1__* inp_stat; } ;
typedef  scalar_t__ nstat_provider_cookie_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_8__ {int /*<<< orphan*/  txbytes; int /*<<< orphan*/  rxbytes; } ;
struct TYPE_7__ {int /*<<< orphan*/  txbytes; int /*<<< orphan*/  rxbytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  txbytes; int /*<<< orphan*/  rxbytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  txbytes; int /*<<< orphan*/  txpackets; int /*<<< orphan*/  rxbytes; int /*<<< orphan*/  rxpackets; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  atomic_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nstat_udp_gone (scalar_t__) ; 

__attribute__((used)) static errno_t
nstat_udp_counts(
	nstat_provider_cookie_t	cookie,
	struct nstat_counts	*out_counts,
	int			*out_gone)
{
	struct nstat_tucookie *tucookie =
	    (struct nstat_tucookie *)cookie;

	if (out_gone) *out_gone = 0;

	// if the pcb is in the dead state, we should stop using it
	if (nstat_udp_gone(cookie))
	{
		if (out_gone) *out_gone = 1;
		if (!tucookie->inp)
			return EINVAL;
	}
	struct inpcb *inp = tucookie->inp;

	atomic_get_64(out_counts->nstat_rxpackets, &inp->inp_stat->rxpackets);
	atomic_get_64(out_counts->nstat_rxbytes, &inp->inp_stat->rxbytes);
	atomic_get_64(out_counts->nstat_txpackets, &inp->inp_stat->txpackets);
	atomic_get_64(out_counts->nstat_txbytes, &inp->inp_stat->txbytes);
	atomic_get_64(out_counts->nstat_cell_rxbytes, &inp->inp_cstat->rxbytes);
	atomic_get_64(out_counts->nstat_cell_txbytes, &inp->inp_cstat->txbytes);
	atomic_get_64(out_counts->nstat_wifi_rxbytes, &inp->inp_wstat->rxbytes);
	atomic_get_64(out_counts->nstat_wifi_txbytes, &inp->inp_wstat->txbytes);
	atomic_get_64(out_counts->nstat_wired_rxbytes, &inp->inp_Wstat->rxbytes);
	atomic_get_64(out_counts->nstat_wired_txbytes, &inp->inp_Wstat->txbytes);

	return 0;
}