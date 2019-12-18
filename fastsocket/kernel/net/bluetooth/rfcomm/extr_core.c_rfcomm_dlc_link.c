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
struct rfcomm_session {int /*<<< orphan*/  dlcs; } ;
struct rfcomm_dlc {struct rfcomm_session* session; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,struct rfcomm_session*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_hold (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_session_clear_timer (struct rfcomm_session*) ; 
 int /*<<< orphan*/  rfcomm_session_hold (struct rfcomm_session*) ; 

__attribute__((used)) static void rfcomm_dlc_link(struct rfcomm_session *s, struct rfcomm_dlc *d)
{
	BT_DBG("dlc %p session %p", d, s);

	rfcomm_session_hold(s);

	rfcomm_session_clear_timer(s);
	rfcomm_dlc_hold(d);
	list_add(&d->list, &s->dlcs);
	d->session = s;
}