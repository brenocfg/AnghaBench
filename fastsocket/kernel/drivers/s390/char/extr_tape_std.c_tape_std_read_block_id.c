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
struct tape_request {scalar_t__ cpdata; scalar_t__ cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {scalar_t__ modeset_byte; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  READ_BLOCK_ID ; 
 int /*<<< orphan*/  TO_RBI ; 
 struct tape_request* tape_alloc_request (int,int) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  tape_ccw_end (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tape_do_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  tape_free_request (struct tape_request*) ; 

int
tape_std_read_block_id(struct tape_device *device, __u64 *id)
{
	struct tape_request *request;
	int rc;

	request = tape_alloc_request(3, 8);
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_RBI;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, READ_BLOCK_ID, 8, request->cpdata);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, NULL);
	/* execute it */
	rc = tape_do_io(device, request);
	if (rc == 0)
		/* Get result from read buffer. */
		*id = *(__u64 *) request->cpdata;
	tape_free_request(request);
	return rc;
}