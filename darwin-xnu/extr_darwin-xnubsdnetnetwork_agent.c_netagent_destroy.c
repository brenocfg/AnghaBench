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
struct netagent_session {int dummy; } ;
typedef  scalar_t__ netagent_session_t ;

/* Variables and functions */
 void netagent_delete_session (struct netagent_session*) ; 

void netagent_destroy(netagent_session_t session)
{
	return netagent_delete_session((struct netagent_session *)session);
}