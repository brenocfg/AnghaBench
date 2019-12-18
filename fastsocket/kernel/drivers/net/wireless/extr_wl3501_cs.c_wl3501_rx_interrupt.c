#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct wl3501_card {int esbq_confirm; int /*<<< orphan*/  sig_pwr_mgmt_confirm; int /*<<< orphan*/  sig_get_confirm; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  sig_id ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
#define  WL3501_SIG_ALARM 140 
#define  WL3501_SIG_ASSOC_CONFIRM 139 
#define  WL3501_SIG_AUTH_CONFIRM 138 
#define  WL3501_SIG_DEAUTH_IND 137 
#define  WL3501_SIG_DISASSOC_IND 136 
#define  WL3501_SIG_GET_CONFIRM 135 
#define  WL3501_SIG_JOIN_CONFIRM 134 
#define  WL3501_SIG_MD_CONFIRM 133 
#define  WL3501_SIG_MD_IND 132 
#define  WL3501_SIG_PWR_MGMT_CONFIRM 131 
#define  WL3501_SIG_RESYNC_CONFIRM 130 
#define  WL3501_SIG_SCAN_CONFIRM 129 
#define  WL3501_SIG_START_CONFIRM 128 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wl3501_alarm_interrupt (struct net_device*,struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_assoc_confirm_interrupt (struct net_device*,int) ; 
 int /*<<< orphan*/  wl3501_auth_confirm_interrupt (struct wl3501_card*,int) ; 
 int /*<<< orphan*/  wl3501_esbq_confirm (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_esbq_confirm_done (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_esbq_req_free (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_get_confirm_interrupt (struct wl3501_card*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wl3501_get_from_wla (struct wl3501_card*,int,int*,int) ; 
 int /*<<< orphan*/  wl3501_md_confirm_interrupt (struct net_device*,struct wl3501_card*,int) ; 
 int /*<<< orphan*/  wl3501_md_ind_interrupt (struct net_device*,struct wl3501_card*,int) ; 
 int /*<<< orphan*/  wl3501_mgmt_join_confirm (struct net_device*,int) ; 
 int /*<<< orphan*/  wl3501_mgmt_resync (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_mgmt_scan_confirm (struct wl3501_card*,int) ; 
 int /*<<< orphan*/  wl3501_start_confirm_interrupt (struct net_device*,struct wl3501_card*,int) ; 

__attribute__((used)) static inline void wl3501_rx_interrupt(struct net_device *dev)
{
	int morepkts;
	u16 addr;
	u8 sig_id;
	struct wl3501_card *this = netdev_priv(dev);

	dprintk(3, "entry");
loop:
	morepkts = 0;
	if (!wl3501_esbq_confirm(this))
		goto free;
	wl3501_get_from_wla(this, this->esbq_confirm, &addr, sizeof(addr));
	wl3501_get_from_wla(this, addr + 2, &sig_id, sizeof(sig_id));

	switch (sig_id) {
	case WL3501_SIG_DEAUTH_IND:
	case WL3501_SIG_DISASSOC_IND:
	case WL3501_SIG_ALARM:
		wl3501_alarm_interrupt(dev, this);
		break;
	case WL3501_SIG_MD_CONFIRM:
		wl3501_md_confirm_interrupt(dev, this, addr);
		break;
	case WL3501_SIG_MD_IND:
		wl3501_md_ind_interrupt(dev, this, addr);
		break;
	case WL3501_SIG_GET_CONFIRM:
		wl3501_get_confirm_interrupt(this, addr,
					     &this->sig_get_confirm,
					     sizeof(this->sig_get_confirm));
		break;
	case WL3501_SIG_PWR_MGMT_CONFIRM:
		wl3501_get_confirm_interrupt(this, addr,
					     &this->sig_pwr_mgmt_confirm,
					    sizeof(this->sig_pwr_mgmt_confirm));
		break;
	case WL3501_SIG_START_CONFIRM:
		wl3501_start_confirm_interrupt(dev, this, addr);
		break;
	case WL3501_SIG_SCAN_CONFIRM:
		wl3501_mgmt_scan_confirm(this, addr);
		break;
	case WL3501_SIG_JOIN_CONFIRM:
		wl3501_mgmt_join_confirm(dev, addr);
		break;
	case WL3501_SIG_ASSOC_CONFIRM:
		wl3501_assoc_confirm_interrupt(dev, addr);
		break;
	case WL3501_SIG_AUTH_CONFIRM:
		wl3501_auth_confirm_interrupt(this, addr);
		break;
	case WL3501_SIG_RESYNC_CONFIRM:
		wl3501_mgmt_resync(this); /* FIXME: should be resync_confirm */
		break;
	}
	wl3501_esbq_confirm_done(this);
	morepkts = 1;
	/* free request if necessary */
free:
	wl3501_esbq_req_free(this);
	if (morepkts)
		goto loop;
}