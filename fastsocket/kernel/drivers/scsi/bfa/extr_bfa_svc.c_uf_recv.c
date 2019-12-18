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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct fchs_s {int dummy; } ;
struct bfi_uf_frm_rcvd_s {size_t buf_tag; int frm_len; int xfr_len; } ;
struct bfa_uf_s {int data_len; int /*<<< orphan*/  hcb_qe; int /*<<< orphan*/ * data_ptr; int /*<<< orphan*/  qe; int /*<<< orphan*/  pb_len; } ;
struct bfa_uf_mod_s {struct bfa_uf_s* uf_list; } ;
struct bfa_uf_buf_s {int /*<<< orphan*/ * d; } ;
struct bfa_s {scalar_t__ fcs; int /*<<< orphan*/  plog; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_PL_EID_RX ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL_UF ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 struct bfa_uf_mod_s* BFA_UF_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __bfa_cb_uf_recv (struct bfa_uf_s*,int /*<<< orphan*/ ) ; 
 void* be16_to_cpu (int) ; 
 int /*<<< orphan*/  bfa_cb_queue (struct bfa_s*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct bfa_uf_s*,int /*<<< orphan*/ ),struct bfa_uf_s*) ; 
 scalar_t__ bfa_mem_get_dmabuf_kva (struct bfa_uf_mod_s*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_plog_fchdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*) ; 
 int /*<<< orphan*/  bfa_plog_fchdr_and_pl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uf_recv(struct bfa_s *bfa, struct bfi_uf_frm_rcvd_s *m)
{
	struct bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);
	u16 uf_tag = m->buf_tag;
	struct bfa_uf_s *uf = &ufm->uf_list[uf_tag];
	struct bfa_uf_buf_s *uf_buf;
	uint8_t *buf;
	struct fchs_s *fchs;

	uf_buf = (struct bfa_uf_buf_s *)
			bfa_mem_get_dmabuf_kva(ufm, uf_tag, uf->pb_len);
	buf = &uf_buf->d[0];

	m->frm_len = be16_to_cpu(m->frm_len);
	m->xfr_len = be16_to_cpu(m->xfr_len);

	fchs = (struct fchs_s *)uf_buf;

	list_del(&uf->qe);	/* dequeue from posted queue */

	uf->data_ptr = buf;
	uf->data_len = m->xfr_len;

	WARN_ON(uf->data_len < sizeof(struct fchs_s));

	if (uf->data_len == sizeof(struct fchs_s)) {
		bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_UF, BFA_PL_EID_RX,
			       uf->data_len, (struct fchs_s *)buf);
	} else {
		u32 pld_w0 = *((u32 *) (buf + sizeof(struct fchs_s)));
		bfa_plog_fchdr_and_pl(bfa->plog, BFA_PL_MID_HAL_UF,
				      BFA_PL_EID_RX, uf->data_len,
				      (struct fchs_s *)buf, pld_w0);
	}

	if (bfa->fcs)
		__bfa_cb_uf_recv(uf, BFA_TRUE);
	else
		bfa_cb_queue(bfa, &uf->hcb_qe, __bfa_cb_uf_recv, uf);
}