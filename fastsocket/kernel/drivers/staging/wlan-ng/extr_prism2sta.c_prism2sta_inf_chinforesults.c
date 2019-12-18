#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ priv; } ;
typedef  TYPE_6__ wlandevice_t ;
struct TYPE_12__ {int scanchannels; TYPE_9__* result; } ;
struct TYPE_16__ {unsigned int count; int /*<<< orphan*/  done; TYPE_1__ results; } ;
struct TYPE_18__ {TYPE_5__ channel_info; } ;
typedef  TYPE_7__ hfa384x_t ;
struct TYPE_14__ {TYPE_2__* result; int /*<<< orphan*/  scanchannels; } ;
struct TYPE_15__ {TYPE_3__ chinforesult; } ;
struct TYPE_19__ {TYPE_4__ info; } ;
typedef  TYPE_8__ hfa384x_InfFrame_t ;
struct TYPE_20__ {int chid; int anl; int pnl; int active; } ;
typedef  TYPE_9__ hfa384x_ChInfoResultSub_t ;
struct TYPE_13__ {int /*<<< orphan*/  active; int /*<<< orphan*/  pnl; int /*<<< orphan*/  anl; int /*<<< orphan*/  chid; } ;

/* Variables and functions */
 int HFA384x_CHINFORESULT_BSSACTIVE ; 
 unsigned int HFA384x_CHINFORESULT_MAX ; 
 int HFA384x_CHINFORESULT_PCFACTIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,int,int,int) ; 

__attribute__((used)) static void prism2sta_inf_chinforesults(wlandevice_t *wlandev,
					hfa384x_InfFrame_t *inf)
{
	hfa384x_t *hw = (hfa384x_t *) wlandev->priv;
	unsigned int i, n;

	hw->channel_info.results.scanchannels =
	    le16_to_cpu(inf->info.chinforesult.scanchannels);

	for (i = 0, n = 0; i < HFA384x_CHINFORESULT_MAX; i++) {
		if (hw->channel_info.results.scanchannels & (1 << i)) {
			int channel =
			    le16_to_cpu(inf->info.chinforesult.result[n].chid) -
			    1;
			hfa384x_ChInfoResultSub_t *chinforesult =
			    &hw->channel_info.results.result[channel];
			chinforesult->chid = channel;
			chinforesult->anl =
			    le16_to_cpu(inf->info.chinforesult.result[n].anl);
			chinforesult->pnl =
			    le16_to_cpu(inf->info.chinforesult.result[n].pnl);
			chinforesult->active =
			    le16_to_cpu(inf->info.chinforesult.result[n].
					active);
			pr_debug
			    ("chinfo: channel %d, %s level (avg/peak)=%d/%d dB, pcf %d\n",
			     channel + 1,
			     chinforesult->
			     active & HFA384x_CHINFORESULT_BSSACTIVE ? "signal"
			     : "noise", chinforesult->anl, chinforesult->pnl,
			     chinforesult->
			     active & HFA384x_CHINFORESULT_PCFACTIVE ? 1 : 0);
			n++;
		}
	}
	atomic_set(&hw->channel_info.done, 2);

	hw->channel_info.count = n;
	return;
}