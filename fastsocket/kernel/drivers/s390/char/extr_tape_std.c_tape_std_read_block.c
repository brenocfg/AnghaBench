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
struct tape_request {scalar_t__ cpaddr; int /*<<< orphan*/  op; } ;
struct TYPE_2__ {int /*<<< orphan*/  idal_buf; } ;
struct tape_device {TYPE_1__ char_data; int /*<<< orphan*/  modeset_byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int /*<<< orphan*/  DBF_EXCEPTION (int,char*) ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  READ_FORWARD ; 
 int /*<<< orphan*/  TO_RFO ; 
 struct tape_request* tape_alloc_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_ccw_end_idal (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct tape_request *
tape_std_read_block(struct tape_device *device, size_t count)
{
	struct tape_request *request;

	/*
	 * We have to alloc 4 ccws in order to be able to transform request
	 * into a read backward request in error case.
	 */
	request = tape_alloc_request(4, 0);
	if (IS_ERR(request)) {
		DBF_EXCEPTION(6, "xrbl fail");
		return request;
	}
	request->op = TO_RFO;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_end_idal(request->cpaddr + 1, READ_FORWARD,
			  device->char_data.idal_buf);
	DBF_EVENT(6, "xrbl ccwg\n");
	return request;
}