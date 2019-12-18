#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int cidcw_ack; } ;
struct TYPE_21__ {scalar_t__ dtmf_ready; } ;
struct TYPE_22__ {TYPE_7__ bits; } ;
struct TYPE_19__ {int dtmf_ready; } ;
struct TYPE_20__ {TYPE_5__ bits; } ;
struct TYPE_17__ {int digit; scalar_t__ dtmf_valid; } ;
struct TYPE_15__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_18__ {TYPE_3__ bits; TYPE_1__ bytes; } ;
struct TYPE_16__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_14__ {int dtmf_proc; int dtmf_state; int dtmf_current; int* dtmfbuffer; size_t dtmf_wp; TYPE_9__ flags; int /*<<< orphan*/  board; TYPE_8__ ex_sig; TYPE_6__ ex; int /*<<< orphan*/  cidcw_wait; TYPE_4__ dtmf; TYPE_2__ ssr; } ;
typedef  TYPE_10__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIG_DTMF_READY ; 
 scalar_t__ ixj_WriteDSPCommand (int,TYPE_10__*) ; 
 int /*<<< orphan*/  ixj_kill_fasync (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ixjdebug ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LineMonitor(IXJ *j)
{
	if (j->dtmf_proc) {
		return -1;
	}
	j->dtmf_proc = 1;

	if (ixj_WriteDSPCommand(0x7000, j))		/* Line Monitor */
		return -1;

	j->dtmf.bytes.high = j->ssr.high;
	j->dtmf.bytes.low = j->ssr.low;
	if (!j->dtmf_state && j->dtmf.bits.dtmf_valid) {
		j->dtmf_state = 1;
		j->dtmf_current = j->dtmf.bits.digit;
	}
	if (j->dtmf_state && !j->dtmf.bits.dtmf_valid)	/* && j->dtmf_wp != j->dtmf_rp) */
	 {
		if(!j->cidcw_wait) {
			j->dtmfbuffer[j->dtmf_wp] = j->dtmf_current;
			j->dtmf_wp++;
			if (j->dtmf_wp == 79)
				j->dtmf_wp = 0;
			j->ex.bits.dtmf_ready = 1;
			if(j->ex_sig.bits.dtmf_ready) {
				ixj_kill_fasync(j, SIG_DTMF_READY, POLL_IN);
			}
		}
		else if(j->dtmf_current == 0x00 || j->dtmf_current == 0x0D) {
			if(ixjdebug & 0x0020) {
				printk("IXJ phone%d saw CIDCW Ack DTMF %d from display at %ld\n", j->board, j->dtmf_current, jiffies);
			}
			j->flags.cidcw_ack = 1;
		}
		j->dtmf_state = 0;
	}
	j->dtmf_proc = 0;

	return 0;
}