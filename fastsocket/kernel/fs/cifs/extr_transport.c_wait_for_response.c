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
struct mid_q_entry {scalar_t__ mid_state; } ;
struct TCP_Server_Info {int /*<<< orphan*/  response_q; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ MID_REQUEST_SUBMITTED ; 
 int wait_event_freezekillable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wait_for_response(struct TCP_Server_Info *server, struct mid_q_entry *midQ)
{
	int error;

	error = wait_event_freezekillable(server->response_q,
				    midQ->mid_state != MID_REQUEST_SUBMITTED);
	if (error < 0)
		return -ERESTARTSYS;

	return 0;
}