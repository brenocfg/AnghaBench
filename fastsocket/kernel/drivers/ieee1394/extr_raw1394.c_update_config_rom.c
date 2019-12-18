#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  recvb; scalar_t__ misc; int /*<<< orphan*/  length; int /*<<< orphan*/  sendb; } ;
struct pending_request {TYPE_1__ req; } ;
struct file_info {int cfgrom_upd; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  free_pending_request (struct pending_request*) ; 
 int hpsb_update_config_rom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  int2ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_config_rom(struct file_info *fi, struct pending_request *req)
{
	int ret = 0;
	quadlet_t *data = kmalloc(req->req.length, GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	if (copy_from_user(data, int2ptr(req->req.sendb), req->req.length)) {
		ret = -EFAULT;
	} else {
		int status = hpsb_update_config_rom(fi->host,
						    data, req->req.length,
						    (unsigned char)req->req.
						    misc);
		if (copy_to_user
		    (int2ptr(req->req.recvb), &status, sizeof(status)))
			ret = -ENOMEM;
	}
	kfree(data);
	if (ret >= 0) {
		free_pending_request(req);	/* we have to free the request, because we queue no response, and therefore nobody will free it */
		fi->cfgrom_upd = 1;
	}
	return ret;
}