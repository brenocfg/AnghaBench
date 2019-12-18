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
struct hidp_session {int /*<<< orphan*/  terminate; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_schedule (struct hidp_session*) ; 

__attribute__((used)) static void hidp_idle_timeout(unsigned long arg)
{
	struct hidp_session *session = (struct hidp_session *) arg;

	atomic_inc(&session->terminate);
	hidp_schedule(session);
}