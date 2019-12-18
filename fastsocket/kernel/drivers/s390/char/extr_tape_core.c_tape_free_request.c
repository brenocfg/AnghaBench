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
struct tape_request {struct tape_request* cpaddr; struct tape_request* cpdata; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*,struct tape_request*) ; 
 int /*<<< orphan*/  kfree (struct tape_request*) ; 
 int /*<<< orphan*/ * tape_put_device (int /*<<< orphan*/ *) ; 

void
tape_free_request (struct tape_request * request)
{
	DBF_LH(6, "Free request %p\n", request);

	if (request->device != NULL) {
		request->device = tape_put_device(request->device);
	}
	kfree(request->cpdata);
	kfree(request->cpaddr);
	kfree(request);
}