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
struct tape_request {scalar_t__ rescnt; int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int /*<<< orphan*/  modeset_byte; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*) ; 
 int /*<<< orphan*/  FORSPACEBLOCK ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_FSB ; 
 struct tape_request* tape_alloc_request (int,int /*<<< orphan*/ ) ; 
 struct ccw1* tape_ccw_cc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ccw1* tape_ccw_end (struct ccw1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ccw1* tape_ccw_repeat (struct ccw1*,int /*<<< orphan*/ ,int) ; 
 int tape_do_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  tape_free_request (struct tape_request*) ; 

int
tape_std_mtfsr(struct tape_device *device, int mt_count)
{
	struct tape_request *request;
	struct ccw1 *ccw;
	int rc;

	request = tape_alloc_request(mt_count + 2, 0);
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_FSB;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, FORSPACEBLOCK, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, NULL);

	/* execute it */
	rc = tape_do_io(device, request);
	if (rc == 0 && request->rescnt > 0) {
		DBF_LH(3, "FSR over tapemark\n");
		rc = 1;
	}
	tape_free_request(request);

	return rc;
}