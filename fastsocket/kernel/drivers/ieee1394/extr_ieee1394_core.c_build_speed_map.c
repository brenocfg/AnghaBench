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
typedef  scalar_t__ u8 ;
struct selfid {scalar_t__ port0; scalar_t__ port1; scalar_t__ port2; scalar_t__ speed; scalar_t__ extended; } ;
struct TYPE_2__ {scalar_t__ lnk_spd; } ;
struct hpsb_host {int selfid_count; int /*<<< orphan*/ * topology_map; TYPE_1__ csr; scalar_t__* speed; scalar_t__* speed_map; } ;
struct ext_selfid {scalar_t__ porta; scalar_t__ portb; scalar_t__ portc; scalar_t__ portd; scalar_t__ porte; scalar_t__ portf; scalar_t__ portg; scalar_t__ porth; } ;

/* Variables and functions */
 scalar_t__ IEEE1394_SPEED_MAX ; 
 scalar_t__ SELFID_PORT_CHILD ; 
 scalar_t__ SELFID_SPEED_UNKNOWN ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void build_speed_map(struct hpsb_host *host, int nodecount)
{
	u8 cldcnt[nodecount];
	u8 *map = host->speed_map;
	u8 *speedcap = host->speed;
	u8 local_link_speed = host->csr.lnk_spd;
	struct selfid *sid;
	struct ext_selfid *esid;
	int i, j, n;

	for (i = 0; i < (nodecount * 64); i += 64) {
		for (j = 0; j < nodecount; j++) {
			map[i+j] = IEEE1394_SPEED_MAX;
		}
	}

	for (i = 0; i < nodecount; i++) {
		cldcnt[i] = 0;
	}

	/* find direct children count and speed */
	for (sid = (struct selfid *)&host->topology_map[host->selfid_count-1],
		     n = nodecount - 1;
	     (void *)sid >= (void *)host->topology_map; sid--) {
		if (sid->extended) {
			esid = (struct ext_selfid *)sid;

			if (esid->porta == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->portb == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->portc == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->portd == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->porte == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->portf == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->portg == SELFID_PORT_CHILD) cldcnt[n]++;
			if (esid->porth == SELFID_PORT_CHILD) cldcnt[n]++;
                } else {
			if (sid->port0 == SELFID_PORT_CHILD) cldcnt[n]++;
			if (sid->port1 == SELFID_PORT_CHILD) cldcnt[n]++;
			if (sid->port2 == SELFID_PORT_CHILD) cldcnt[n]++;

			speedcap[n] = sid->speed;
			if (speedcap[n] > local_link_speed)
				speedcap[n] = local_link_speed;
			n--;
		}
	}

	/* set self mapping */
	for (i = 0; i < nodecount; i++) {
		map[64*i + i] = speedcap[i];
	}

	/* fix up direct children count to total children count;
	 * also fix up speedcaps for sibling and parent communication */
	for (i = 1; i < nodecount; i++) {
		for (j = cldcnt[i], n = i - 1; j > 0; j--) {
			cldcnt[i] += cldcnt[n];
			speedcap[n] = min(speedcap[n], speedcap[i]);
			n -= cldcnt[n] + 1;
		}
	}

	for (n = 0; n < nodecount; n++) {
		for (i = n - cldcnt[n]; i <= n; i++) {
			for (j = 0; j < (n - cldcnt[n]); j++) {
				map[j*64 + i] = map[i*64 + j] =
					min(map[i*64 + j], speedcap[n]);
			}
			for (j = n + 1; j < nodecount; j++) {
				map[j*64 + i] = map[i*64 + j] =
					min(map[i*64 + j], speedcap[n]);
			}
		}
	}

	/* assume a maximum speed for 1394b PHYs, nodemgr will correct it */
	if (local_link_speed > SELFID_SPEED_UNKNOWN)
		for (i = 0; i < nodecount; i++)
			if (speedcap[i] == SELFID_SPEED_UNKNOWN)
				speedcap[i] = local_link_speed;
}