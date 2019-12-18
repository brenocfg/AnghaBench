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
struct tape_request {int /*<<< orphan*/  cpdata; int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MEDIUM_SENSE ; 
 int /*<<< orphan*/  TO_MSEN ; 
 struct tape_request* tape_alloc_request (int,int) ; 
 int /*<<< orphan*/  tape_ccw_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_do_io_async_free (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static void tape_3590_sense_medium_async(struct tape_device *device)
{
	struct tape_request *request;

	request = tape_alloc_request(1, 128);
	if (IS_ERR(request))
		return;
	request->op = TO_MSEN;
	tape_ccw_end(request->cpaddr, MEDIUM_SENSE, 128, request->cpdata);
	tape_do_io_async_free(device, request);
}