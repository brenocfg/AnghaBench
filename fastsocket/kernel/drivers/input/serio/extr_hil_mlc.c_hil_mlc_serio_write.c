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
typedef  scalar_t__ uint8_t ;
struct serio_driver {int /*<<< orphan*/  (* interrupt ) (struct serio*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct serio {struct serio_driver* drv; struct hil_mlc_serio_map* port_data; } ;
struct hil_mlc_serio_map {size_t didx; struct hil_mlc* mlc; } ;
struct hil_mlc {int* serio_opacket; int* serio_oidx; TYPE_1__* di; } ;
typedef  int hil_packet ;
struct TYPE_2__ {scalar_t__* rnm; scalar_t__* exd; scalar_t__* rsc; scalar_t__* idd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
#define  HIL_CMD_EXD 131 
#define  HIL_CMD_IDD 130 
#define  HIL_CMD_RNM 129 
#define  HIL_CMD_RSC 128 
 int HIL_ERR_INT ; 
 int HIL_PKT_CMD ; 
 int HIL_PKT_DATA_MASK ; 
 int /*<<< orphan*/  stub1 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct serio*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct serio*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct serio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct serio*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hil_mlc_serio_write(struct serio *serio, unsigned char c)
{
	struct hil_mlc_serio_map *map;
	struct hil_mlc *mlc;
	struct serio_driver *drv;
	uint8_t *idx, *last;

	map = serio->port_data;
	BUG_ON(map == NULL);

	mlc = map->mlc;
	BUG_ON(mlc == NULL);

	mlc->serio_opacket[map->didx] |=
		((hil_packet)c) << (8 * (3 - mlc->serio_oidx[map->didx]));

	if (mlc->serio_oidx[map->didx] >= 3) {
		/* for now only commands */
		if (!(mlc->serio_opacket[map->didx] & HIL_PKT_CMD))
			return -EIO;
		switch (mlc->serio_opacket[map->didx] & HIL_PKT_DATA_MASK) {
		case HIL_CMD_IDD:
			idx = mlc->di[map->didx].idd;
			goto emu;
		case HIL_CMD_RSC:
			idx = mlc->di[map->didx].rsc;
			goto emu;
		case HIL_CMD_EXD:
			idx = mlc->di[map->didx].exd;
			goto emu;
		case HIL_CMD_RNM:
			idx = mlc->di[map->didx].rnm;
			goto emu;
		default:
			break;
		}
		mlc->serio_oidx[map->didx] = 0;
		mlc->serio_opacket[map->didx] = 0;
	}

	mlc->serio_oidx[map->didx]++;
	return -EIO;
 emu:
	drv = serio->drv;
	BUG_ON(drv == NULL);

	last = idx + 15;
	while ((last != idx) && (*last == 0))
		last--;

	while (idx != last) {
		drv->interrupt(serio, 0, 0);
		drv->interrupt(serio, HIL_ERR_INT >> 16, 0);
		drv->interrupt(serio, 0, 0);
		drv->interrupt(serio, *idx, 0);
		idx++;
	}
	drv->interrupt(serio, 0, 0);
	drv->interrupt(serio, HIL_ERR_INT >> 16, 0);
	drv->interrupt(serio, HIL_PKT_CMD >> 8, 0);
	drv->interrupt(serio, *idx, 0);

	mlc->serio_oidx[map->didx] = 0;
	mlc->serio_opacket[map->didx] = 0;

	return 0;
}