#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zatm_dev {int chans; TYPE_2__* pool_info; int /*<<< orphan*/  rx_map; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_3__ {int vci_bits; } ;
struct atm_dev {TYPE_1__ ci_range; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_thres; scalar_t__ next_cnt; scalar_t__ next_off; scalar_t__ offset; int /*<<< orphan*/  high_water; int /*<<< orphan*/  low_water; scalar_t__ rqu_count; scalar_t__ rqa_count; scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIGH_MARK ; 
 int /*<<< orphan*/  LOW_MARK ; 
 int /*<<< orphan*/  OFF_CNG_THRES ; 
 struct zatm_dev* ZATM_DEV (struct atm_dev*) ; 
 int ZATM_LAST_POOL ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uPD98401_VRR ; 
 int /*<<< orphan*/  zpokel (struct zatm_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_rx(struct atm_dev *dev)
{
	struct zatm_dev *zatm_dev;
	int size,i;

DPRINTK("start_rx\n");
	zatm_dev = ZATM_DEV(dev);
	size = sizeof(struct atm_vcc *)*zatm_dev->chans;
	zatm_dev->rx_map =  kzalloc(size,GFP_KERNEL);
	if (!zatm_dev->rx_map) return -ENOMEM;
	/* set VPI/VCI split (use all VCIs and give what's left to VPIs) */
	zpokel(zatm_dev,(1 << dev->ci_range.vci_bits)-1,uPD98401_VRR);
	/* prepare free buffer pools */
	for (i = 0; i <= ZATM_LAST_POOL; i++) {
		zatm_dev->pool_info[i].ref_count = 0;
		zatm_dev->pool_info[i].rqa_count = 0;
		zatm_dev->pool_info[i].rqu_count = 0;
		zatm_dev->pool_info[i].low_water = LOW_MARK;
		zatm_dev->pool_info[i].high_water = HIGH_MARK;
		zatm_dev->pool_info[i].offset = 0;
		zatm_dev->pool_info[i].next_off = 0;
		zatm_dev->pool_info[i].next_cnt = 0;
		zatm_dev->pool_info[i].next_thres = OFF_CNG_THRES;
	}
	return 0;
}