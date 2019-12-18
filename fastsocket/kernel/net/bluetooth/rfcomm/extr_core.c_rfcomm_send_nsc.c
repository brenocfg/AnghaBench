#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u8 ;
struct rfcomm_session {int /*<<< orphan*/  initiator; } ;
struct rfcomm_mcc {void* len; void* type; } ;
struct rfcomm_hdr {void* len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int,void*) ; 
 void* RFCOMM_NSC ; 
 int /*<<< orphan*/  RFCOMM_UIH ; 
 int /*<<< orphan*/  __addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __fcs (void**) ; 
 void* __len8 (int) ; 
 void* __mcc_type (int,void*) ; 
 int rfcomm_send_frame (struct rfcomm_session*,void**,int) ; 

__attribute__((used)) static int rfcomm_send_nsc(struct rfcomm_session *s, int cr, u8 type)
{
	struct rfcomm_hdr *hdr;
	struct rfcomm_mcc *mcc;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d type %d", s, cr, type);

	hdr = (void *) ptr; ptr += sizeof(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(sizeof(*mcc) + 1);

	mcc = (void *) ptr; ptr += sizeof(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_NSC);
	mcc->len  = __len8(1);

	/* Type that we didn't like */
	*ptr = __mcc_type(cr, type); ptr++;

	*ptr = __fcs(buf); ptr++;

	return rfcomm_send_frame(s, buf, ptr - buf);
}