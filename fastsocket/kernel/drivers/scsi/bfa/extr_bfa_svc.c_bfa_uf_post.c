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
struct bfi_uf_buf_post_s {int /*<<< orphan*/  mh; } ;
struct bfa_uf_s {size_t uf_tag; int /*<<< orphan*/  qe; } ;
struct bfa_uf_mod_s {int /*<<< orphan*/  uf_posted_q; int /*<<< orphan*/  bfa; int /*<<< orphan*/ * uf_buf_posts; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_REQQ_FCXP ; 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 struct bfi_uf_buf_post_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct bfi_uf_buf_post_s*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bfa_status_t
bfa_uf_post(struct bfa_uf_mod_s *ufm, struct bfa_uf_s *uf)
{
	struct bfi_uf_buf_post_s *uf_post_msg;

	uf_post_msg = bfa_reqq_next(ufm->bfa, BFA_REQQ_FCXP);
	if (!uf_post_msg)
		return BFA_STATUS_FAILED;

	memcpy(uf_post_msg, &ufm->uf_buf_posts[uf->uf_tag],
		      sizeof(struct bfi_uf_buf_post_s));
	bfa_reqq_produce(ufm->bfa, BFA_REQQ_FCXP, uf_post_msg->mh);

	bfa_trc(ufm->bfa, uf->uf_tag);

	list_add_tail(&uf->qe, &ufm->uf_posted_q);
	return BFA_STATUS_OK;
}