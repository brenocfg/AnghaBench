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
struct adb_request {int complete; int /*<<< orphan*/  (* done ) (struct adb_request*) ;int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int adb_iop_state ; 
 int /*<<< orphan*/  current_req ; 
 int /*<<< orphan*/  stub1 (struct adb_request*) ; 

__attribute__((used)) static void adb_iop_end_req(struct adb_request *req, int state)
{
	req->complete = 1;
	current_req = req->next;
	if (req->done) (*req->done)(req);
	adb_iop_state = state;
}