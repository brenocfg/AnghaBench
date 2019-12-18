#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  bbp_type; int /*<<< orphan*/  long_retry; int /*<<< orphan*/  short_retry; int /*<<< orphan*/  channel_num; int /*<<< orphan*/  data_rate; int /*<<< orphan*/  frag_thresh; int /*<<< orphan*/  rts_thresh; int /*<<< orphan*/  int_works; int /*<<< orphan*/ * nTxDescs; int /*<<< orphan*/  nRxDescs1; int /*<<< orphan*/  nRxDescs0; } ;
struct TYPE_4__ {TYPE_2__ sOpts; } ;
typedef  TYPE_1__* PSDevice ;
typedef  TYPE_2__* POPTIONS ;

/* Variables and functions */
 int /*<<< orphan*/  BBP_TYPE_DEF ; 
 int /*<<< orphan*/  CHANNEL_DEF ; 
 int /*<<< orphan*/  DATA_RATE_DEF ; 
 int /*<<< orphan*/  DEVICE_FLAGS_80211h_MODE ; 
 int /*<<< orphan*/  DEVICE_FLAGS_DiversityANT ; 
 int /*<<< orphan*/  DEVICE_FLAGS_IP_ALIGN ; 
 int /*<<< orphan*/  DEVICE_FLAGS_OP_MODE ; 
 int /*<<< orphan*/  DEVICE_FLAGS_PREAMBLE_TYPE ; 
 int /*<<< orphan*/  FRAG_THRESH_DEF ; 
 int /*<<< orphan*/  INT_WORKS_DEF ; 
 int /*<<< orphan*/  LONG_RETRY_DEF ; 
 int /*<<< orphan*/  RTS_THRESH_DEF ; 
 int /*<<< orphan*/  RX_DESC_DEF0 ; 
 int /*<<< orphan*/  RX_DESC_DEF1 ; 
 int /*<<< orphan*/  SHORT_RETRY_DEF ; 
 int /*<<< orphan*/  TX_DESC_DEF0 ; 
 int /*<<< orphan*/  TX_DESC_DEF1 ; 

__attribute__((used)) static void
device_get_options(PSDevice pDevice, int index, char* devname) {

    POPTIONS pOpts = &(pDevice->sOpts);
  pOpts->nRxDescs0=RX_DESC_DEF0;
  pOpts->nRxDescs1=RX_DESC_DEF1;
  pOpts->nTxDescs[0]=TX_DESC_DEF0;
  pOpts->nTxDescs[1]=TX_DESC_DEF1;
pOpts->flags|=DEVICE_FLAGS_IP_ALIGN;
  pOpts->int_works=INT_WORKS_DEF;
  pOpts->rts_thresh=RTS_THRESH_DEF;
  pOpts->frag_thresh=FRAG_THRESH_DEF;
  pOpts->data_rate=DATA_RATE_DEF;
  pOpts->channel_num=CHANNEL_DEF;

pOpts->flags|=DEVICE_FLAGS_PREAMBLE_TYPE;
pOpts->flags|=DEVICE_FLAGS_OP_MODE;
//pOpts->flags|=DEVICE_FLAGS_PS_MODE;
  pOpts->short_retry=SHORT_RETRY_DEF;
  pOpts->long_retry=LONG_RETRY_DEF;
  pOpts->bbp_type=BBP_TYPE_DEF;
pOpts->flags|=DEVICE_FLAGS_80211h_MODE;
pOpts->flags|=DEVICE_FLAGS_DiversityANT;


}