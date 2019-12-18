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
struct secasvar {scalar_t__ natt_last_activity; TYPE_1__* sah; } ;
struct secasindex {int /*<<< orphan*/  mode; int /*<<< orphan*/  proto; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  saidx_swap_sent_addr ;
struct TYPE_2__ {struct secasindex saidx; } ;

/* Variables and functions */
 int CMP_MODE ; 
 int CMP_PORT ; 
 int /*<<< orphan*/  bzero (struct secasindex*,int) ; 
 scalar_t__ key_cmpsaidx (struct secasindex*,struct secasindex*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ natt_now ; 

__attribute__((used)) static void
key_update_natt_keepalive_timestamp (struct secasvar *sav_sent,
									 struct secasvar *sav_update)
{
	struct secasindex saidx_swap_sent_addr;
	
	// exit early if two SAs are identical, or if sav_update is current
	if (sav_sent == sav_update ||
	    sav_update->natt_last_activity == natt_now) {
		return;
	}
	
	// assuming that (sav_update->remote_ike_port != 0 && (esp_udp_encap_port & 0xFFFF) != 0)
	
	bzero(&saidx_swap_sent_addr, sizeof(saidx_swap_sent_addr));
	memcpy(&saidx_swap_sent_addr.src, &sav_sent->sah->saidx.dst, sizeof(saidx_swap_sent_addr.src));
	memcpy(&saidx_swap_sent_addr.dst, &sav_sent->sah->saidx.src, sizeof(saidx_swap_sent_addr.dst));
	saidx_swap_sent_addr.proto = sav_sent->sah->saidx.proto;
	saidx_swap_sent_addr.mode = sav_sent->sah->saidx.mode;
	// we ignore reqid for split-tunnel setups
	
	if (key_cmpsaidx(&sav_sent->sah->saidx, &sav_update->sah->saidx, CMP_MODE | CMP_PORT) ||
	    key_cmpsaidx(&saidx_swap_sent_addr, &sav_update->sah->saidx, CMP_MODE | CMP_PORT)) {
		sav_update->natt_last_activity = natt_now;
	}
}