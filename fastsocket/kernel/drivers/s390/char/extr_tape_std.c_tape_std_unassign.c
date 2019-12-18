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
struct tape_request {scalar_t__ cpaddr; int /*<<< orphan*/  cpdata; int /*<<< orphan*/  op; } ;
struct tape_device {scalar_t__ tape_state; int /*<<< orphan*/  cdev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_UNASSIGN ; 
 scalar_t__ TS_NOT_OPER ; 
 int /*<<< orphan*/  UNASSIGN ; 
 struct tape_request* tape_alloc_request (int,int) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_ccw_end (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tape_do_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  tape_free_request (struct tape_request*) ; 

int
tape_std_unassign (struct tape_device *device)
{
	int                  rc;
	struct tape_request *request;

	if (device->tape_state == TS_NOT_OPER) {
		DBF_EVENT(3, "(%08x): Can't unassign device\n",
			device->cdev_id);
		return -EIO;
	}

	request = tape_alloc_request(2, 11);
	if (IS_ERR(request))
		return PTR_ERR(request);

	request->op = TO_UNASSIGN;
	tape_ccw_cc(request->cpaddr, UNASSIGN, 11, request->cpdata);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, NULL);

	if ((rc = tape_do_io(device, request)) != 0) {
		DBF_EVENT(3, "%08x: Unassign failed\n", device->cdev_id);
	} else {
		DBF_EVENT(3, "%08x: Tape unassigned\n", device->cdev_id);
	}
	tape_free_request(request);
	return rc;
}