#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ word ;
struct TYPE_15__ {int /*<<< orphan*/  count; } ;
struct TYPE_14__ {int complete; int RNum; int RNR; TYPE_4__* R; int /*<<< orphan*/  IndCh; int /*<<< orphan*/  Id; int /*<<< orphan*/  RLength; } ;
struct TYPE_16__ {int status; TYPE_6__ rc; TYPE_5__ e; int /*<<< orphan*/  data; TYPE_1__* adapter; } ;
typedef  TYPE_7__ divas_um_idi_entity_t ;
struct TYPE_11__ {int /*<<< orphan*/  IndCh; int /*<<< orphan*/  Ind; } ;
struct TYPE_12__ {TYPE_2__ ind; } ;
struct TYPE_17__ {scalar_t__ data_length; TYPE_3__ hdr; int /*<<< orphan*/  type; } ;
typedef  TYPE_8__ diva_um_idi_ind_hdr_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_13__ {scalar_t__ PLength; int /*<<< orphan*/ * P; } ;
struct TYPE_10__ {int /*<<< orphan*/  adapter_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRC (char*) ; 
 int /*<<< orphan*/  DIVA_UM_IDI_IND ; 
 int DIVA_UM_IDI_RC_PENDING ; 
 int /*<<< orphan*/  diva_data_q_ack_segment4write (int /*<<< orphan*/ *,int) ; 
 int diva_data_q_get_max_length (int /*<<< orphan*/ *) ; 
 scalar_t__ diva_data_q_get_segment4write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_idi_ind(divas_um_idi_entity_t * e, byte ind)
{
	int do_wakeup = 0;

	if (e->e.complete != 0x02) {
		diva_um_idi_ind_hdr_t *pind =
		    (diva_um_idi_ind_hdr_t *)
		    diva_data_q_get_segment4write(&e->data);
		if (pind) {
			e->e.RNum = 1;
			e->e.R->P = (byte *) & pind[1];
			e->e.R->PLength =
			    (word) (diva_data_q_get_max_length(&e->data) -
				    sizeof(*pind));
			DBG_TRC(("A(%d) E(%08x) ind_1(%02x-%02x-%02x)-[%d-%d]",
				 e->adapter->adapter_nr, e, e->e.Id, ind,
				 e->e.IndCh, e->e.RLength,
				 e->e.R->PLength));

		} else {
			DBG_TRC(("A(%d) E(%08x) ind(%02x-%02x-%02x)-RNR",
				 e->adapter->adapter_nr, e, e->e.Id, ind,
				 e->e.IndCh));
			e->e.RNum = 0;
			e->e.RNR = 1;
			do_wakeup = 1;
		}
	} else {
		diva_um_idi_ind_hdr_t *pind =
		    (diva_um_idi_ind_hdr_t *) (e->e.R->P);

		DBG_TRC(("A(%d) E(%08x) ind(%02x-%02x-%02x)-[%d]",
			 e->adapter->adapter_nr, e, e->e.Id, ind,
			 e->e.IndCh, e->e.R->PLength));

		pind--;
		pind->type = DIVA_UM_IDI_IND;
		pind->hdr.ind.Ind = ind;
		pind->hdr.ind.IndCh = e->e.IndCh;
		pind->data_length = e->e.R->PLength;
		diva_data_q_ack_segment4write(&e->data,
					      (int) (sizeof(*pind) +
						     e->e.R->PLength));
		do_wakeup = 1;
	}

	if ((e->status & DIVA_UM_IDI_RC_PENDING) && !e->rc.count) {
		do_wakeup = 0;
	}

	return (do_wakeup);
}