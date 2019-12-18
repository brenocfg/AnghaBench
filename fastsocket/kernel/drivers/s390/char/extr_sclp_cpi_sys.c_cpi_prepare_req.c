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
struct sclp_req {int /*<<< orphan*/  callback; int /*<<< orphan*/  status; struct cpi_sccb* sccb; int /*<<< orphan*/  command; } ;
struct TYPE_4__ {int length; int type; } ;
struct cpi_evbuf {int /*<<< orphan*/  sysplex_name; int /*<<< orphan*/  system_level; int /*<<< orphan*/  system_name; int /*<<< orphan*/  system_type; TYPE_2__ header; } ;
struct TYPE_3__ {int length; } ;
struct cpi_sccb {struct cpi_evbuf cpi_evbuf; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sclp_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 int /*<<< orphan*/  SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  cpi_callback ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  kfree (struct sclp_req*) ; 
 struct sclp_req* kzalloc (int,int) ; 
 int /*<<< orphan*/  set_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysplex_name ; 
 int /*<<< orphan*/  system_level ; 
 int /*<<< orphan*/  system_name ; 
 int /*<<< orphan*/  system_type ; 

__attribute__((used)) static struct sclp_req *cpi_prepare_req(void)
{
	struct sclp_req *req;
	struct cpi_sccb *sccb;
	struct cpi_evbuf *evb;

	req = kzalloc(sizeof(struct sclp_req), GFP_KERNEL);
	if (!req)
		return ERR_PTR(-ENOMEM);
	sccb = (struct cpi_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!sccb) {
		kfree(req);
		return ERR_PTR(-ENOMEM);
	}

	/* setup SCCB for Control-Program Identification */
	sccb->header.length = sizeof(struct cpi_sccb);
	sccb->cpi_evbuf.header.length = sizeof(struct cpi_evbuf);
	sccb->cpi_evbuf.header.type = 0x0b;
	evb = &sccb->cpi_evbuf;

	/* set system type */
	set_data(evb->system_type, system_type);

	/* set system name */
	set_data(evb->system_name, system_name);

	/* set sytem level */
	evb->system_level = system_level;

	/* set sysplex name */
	set_data(evb->sysplex_name, sysplex_name);

	/* prepare request data structure presented to SCLP driver */
	req->command = SCLP_CMDW_WRITE_EVENT_DATA;
	req->sccb = sccb;
	req->status = SCLP_REQ_FILLED;
	req->callback = cpi_callback;
	return req;
}