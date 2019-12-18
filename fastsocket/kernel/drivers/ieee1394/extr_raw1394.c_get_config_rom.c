#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; int /*<<< orphan*/  sendb; int /*<<< orphan*/  address; int /*<<< orphan*/  tag; int /*<<< orphan*/  recvb; } ;
struct pending_request {TYPE_4__ req; } ;
struct file_info {TYPE_3__* host; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int quadlet_t ;
struct TYPE_10__ {TYPE_1__* cache_head; } ;
struct TYPE_7__ {int generation; TYPE_5__* rom; } ;
struct TYPE_8__ {TYPE_2__ csr; } ;
struct TYPE_6__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR1212_CONFIG_ROM_SPACE_OFFSET ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int*,int) ; 
 int csr1212_read (TYPE_5__*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  free_pending_request (struct pending_request*) ; 
 int /*<<< orphan*/  int2ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_config_rom(struct file_info *fi, struct pending_request *req)
{
	int ret = 0;
	quadlet_t *data = kmalloc(req->req.length, GFP_KERNEL);
	int status;

	if (!data)
		return -ENOMEM;

	status =
	    csr1212_read(fi->host->csr.rom, CSR1212_CONFIG_ROM_SPACE_OFFSET,
			 data, req->req.length);
	if (copy_to_user(int2ptr(req->req.recvb), data, req->req.length))
		ret = -EFAULT;
	if (copy_to_user
	    (int2ptr(req->req.tag), &fi->host->csr.rom->cache_head->len,
	     sizeof(fi->host->csr.rom->cache_head->len)))
		ret = -EFAULT;
	if (copy_to_user(int2ptr(req->req.address), &fi->host->csr.generation,
			 sizeof(fi->host->csr.generation)))
		ret = -EFAULT;
	if (copy_to_user(int2ptr(req->req.sendb), &status, sizeof(status)))
		ret = -EFAULT;
	kfree(data);
	if (ret >= 0) {
		free_pending_request(req);	/* we have to free the request, because we queue no response, and therefore nobody will free it */
	}
	return ret;
}