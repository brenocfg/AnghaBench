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
struct netagent_session {void* event_context; int /*<<< orphan*/  event_handler; } ;
typedef  struct netagent_session* netagent_session_t ;
typedef  int /*<<< orphan*/  netagent_event_f ;

/* Variables and functions */
 struct netagent_session* netagent_create_session (int /*<<< orphan*/ ) ; 

netagent_session_t netagent_create(netagent_event_f event_handler, void *context)
{
	struct netagent_session *session = netagent_create_session(0);
	if (session == NULL) {
		return NULL;
	}

	session->event_handler = event_handler;
	session->event_context = context;
	return session;
}