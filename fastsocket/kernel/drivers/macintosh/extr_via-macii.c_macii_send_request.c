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
struct adb_request {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  macii_poll () ; 
 int macii_write (struct adb_request*) ; 
 int /*<<< orphan*/  request_is_queued (struct adb_request*) ; 

__attribute__((used)) static int macii_send_request(struct adb_request *req, int sync)
{
	int err;
	unsigned long flags;

	BUG_ON(request_is_queued(req));

	local_irq_save(flags);
	err = macii_write(req);
	local_irq_restore(flags);

	if (!err && sync) {
		while (!req->complete) {
			macii_poll();
		}
		BUG_ON(request_is_queued(req));
	}

	return err;
}