#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int high; int low; } ;
struct TYPE_11__ {int high; int low; } ;
struct TYPE_10__ {int low; } ;
struct TYPE_13__ {int /*<<< orphan*/  cid_play_aec_level; TYPE_3__ baseframe; TYPE_2__ ssr; TYPE_1__ dsp; int /*<<< orphan*/  aec_level; } ;
typedef  TYPE_4__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  aec_stop (TYPE_4__*) ; 
 scalar_t__ idle (TYPE_4__*) ; 
 scalar_t__ ixj_WriteDSPCommand (unsigned short,TYPE_4__*) ; 
 int /*<<< orphan*/  ixj_aec_start (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_base_frame(IXJ *j, int size)
{
	unsigned short cmd;
	int cnt;

	idle(j);
	j->cid_play_aec_level = j->aec_level;
	aec_stop(j);
	for (cnt = 0; cnt < 10; cnt++) {
		if (idle(j))
			break;
	}
	if (j->ssr.high || j->ssr.low)
		return -1;
	if (j->dsp.low != 0x20) {
		switch (size) {
		case 30:
			cmd = 0x07F0;
			/* Set Base Frame Size to 240 pg9-10 8021 */
			break;
		case 20:
			cmd = 0x07A0;
			/* Set Base Frame Size to 160 pg9-10 8021 */
			break;
		case 10:
			cmd = 0x0750;
			/* Set Base Frame Size to 80 pg9-10 8021 */
			break;
		default:
			return -1;
		}
	} else {
		if (size == 30)
			return size;
		else
			return -1;
	}
	if (ixj_WriteDSPCommand(cmd, j)) {
		j->baseframe.high = j->baseframe.low = 0xFF;
		return -1;
	} else {
		j->baseframe.high = j->ssr.high;
		j->baseframe.low = j->ssr.low;
		/* If the status returned is 0x0000 (pg9-9 8021) the call failed */
		if(j->baseframe.high == 0x00 && j->baseframe.low == 0x00) {
			return -1;
		}
	}
	ixj_aec_start(j, j->cid_play_aec_level);
	return size;
}