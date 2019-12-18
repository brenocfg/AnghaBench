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
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int magic; int /*<<< orphan*/  flags; struct dasd_ccw_req* cpaddr; int /*<<< orphan*/ * data; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_USE_ERP ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dasd_ccw_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 struct dasd_ccw_req* kcalloc (int,int,int) ; 
 int /*<<< orphan*/  kfree (struct dasd_ccw_req*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct dasd_ccw_req *dasd_kmalloc_request(int magic, int cplength,
					  int datasize,
					  struct dasd_device *device)
{
	struct dasd_ccw_req *cqr;

	/* Sanity checks */
	BUG_ON(datasize > PAGE_SIZE ||
	     (cplength*sizeof(struct ccw1)) > PAGE_SIZE);

	cqr = kzalloc(sizeof(struct dasd_ccw_req), GFP_ATOMIC);
	if (cqr == NULL)
		return ERR_PTR(-ENOMEM);
	cqr->cpaddr = NULL;
	if (cplength > 0) {
		cqr->cpaddr = kcalloc(cplength, sizeof(struct ccw1),
				      GFP_ATOMIC | GFP_DMA);
		if (cqr->cpaddr == NULL) {
			kfree(cqr);
			return ERR_PTR(-ENOMEM);
		}
	}
	cqr->data = NULL;
	if (datasize > 0) {
		cqr->data = kzalloc(datasize, GFP_ATOMIC | GFP_DMA);
		if (cqr->data == NULL) {
			kfree(cqr->cpaddr);
			kfree(cqr);
			return ERR_PTR(-ENOMEM);
		}
	}
	cqr->magic =  magic;
	set_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	dasd_get_device(device);
	return cqr;
}