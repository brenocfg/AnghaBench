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
struct scatterlist {int dummy; } ;
struct cxgbi_tag_format {int dummy; } ;
struct cxgbi_sock {int /*<<< orphan*/  tid; struct cxgbi_device* cdev; } ;
struct cxgbi_gather_list {int dummy; } ;
struct cxgbi_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  ddp; struct cxgbi_tag_format tag_format; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CXGBI_DBG_DDP ; 
 scalar_t__ DDP_PGIDX_MAX ; 
 unsigned int DDP_THRESHOLD ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cxgbi_sw_tag_usable (struct cxgbi_tag_format*,unsigned int) ; 
 struct cxgbi_gather_list* ddp_make_gl (unsigned int,struct scatterlist*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddp_release_gl (struct cxgbi_gather_list*,int /*<<< orphan*/ ) ; 
 int ddp_tag_reserve (struct cxgbi_sock*,int /*<<< orphan*/ ,unsigned int,unsigned int*,struct cxgbi_gather_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,unsigned int,...) ; 
 scalar_t__ page_idx ; 

int cxgbi_ddp_reserve(struct cxgbi_sock *csk, unsigned int *tagp,
			unsigned int sw_tag, unsigned int xferlen,
			struct scatterlist *sgl, unsigned int sgcnt, gfp_t gfp)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct cxgbi_tag_format *tformat = &cdev->tag_format;
	struct cxgbi_gather_list *gl;
	int err;

	if (page_idx >= DDP_PGIDX_MAX || !cdev->ddp ||
	    xferlen < DDP_THRESHOLD) {
		log_debug(1 << CXGBI_DBG_DDP,
			"pgidx %u, xfer %u, NO ddp.\n", page_idx, xferlen);
		return -EINVAL;
	}

	if (!cxgbi_sw_tag_usable(tformat, sw_tag)) {
		log_debug(1 << CXGBI_DBG_DDP,
			"sw_tag 0x%x NOT usable.\n", sw_tag);
		return -EINVAL;
	}

	gl = ddp_make_gl(xferlen, sgl, sgcnt, cdev->pdev, gfp);
	if (!gl)
		return -ENOMEM;

	err = ddp_tag_reserve(csk, csk->tid, sw_tag, tagp, gl, gfp);
	if (err < 0)
		ddp_release_gl(gl, cdev->pdev);

	return err;
}