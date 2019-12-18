#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct frame {int dummy; } ;
struct carlu_tx_info {TYPE_2__* rates; } ;
struct carlu {int dummy; } ;
struct TYPE_4__ {unsigned int ext; } ;
struct carl9170_rsp {TYPE_3__* _tx_status; TYPE_1__ hdr; } ;
struct TYPE_6__ {unsigned int info; int /*<<< orphan*/  cookie; } ;
struct TYPE_5__ {int cnt; int rix; } ;

/* Variables and functions */
 unsigned int CARL9170_TX_MAX_RATES ; 
 unsigned int CARL9170_TX_STATUS_QUEUE ; 
 unsigned int CARL9170_TX_STATUS_QUEUE_S ; 
 unsigned int CARL9170_TX_STATUS_RIX ; 
 unsigned int CARL9170_TX_STATUS_RIX_S ; 
 int CARL9170_TX_STATUS_TRIES ; 
 int CARL9170_TX_STATUS_TRIES_S ; 
 struct frame* carlu_find_frame (struct carlu*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carlu_free_dev_mem (struct carlu*,struct frame*) ; 
 int /*<<< orphan*/  carlu_tx_fb_cb (struct carlu*,struct frame*) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 struct carlu_tx_info* get_tx_info (struct frame*) ; 

void carlu_tx_feedback(struct carlu *ar,
		       struct carl9170_rsp *cmd)
{
	unsigned int i, n, k, q;
	struct frame *frame;
	struct carlu_tx_info *tx_info;

	n = cmd->hdr.ext;

	for (i = 0; i < n; i++) {
		q = (cmd->_tx_status[i].info >> CARL9170_TX_STATUS_QUEUE_S) &
		    CARL9170_TX_STATUS_QUEUE;
		frame = carlu_find_frame(ar, q, cmd->_tx_status[i].cookie);
		if (frame) {
			carlu_free_dev_mem(ar, frame);
			tx_info = get_tx_info(frame);

			k = (cmd->_tx_status[i].info >> CARL9170_TX_STATUS_RIX)
			    & CARL9170_TX_STATUS_RIX_S;
			tx_info->rates[k].cnt = (cmd->_tx_status[i].info >>
						 CARL9170_TX_STATUS_TRIES_S) &
						CARL9170_TX_STATUS_TRIES;
			for (k++; k < CARL9170_TX_MAX_RATES; k++) {
				tx_info->rates[k].rix = -1;
				tx_info->rates[k].cnt = -1;
			}

			carlu_tx_fb_cb(ar, frame);
		} else {
			err("Found no frame for cookie %d.\n",
			    cmd->_tx_status[i].cookie);
		}
	}
}