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
struct smsg_app_event {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ SMSG_PREFIX ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ sender ; 
 struct smsg_app_event* smsg_app_event_alloc (char const*,char*) ; 
 int /*<<< orphan*/  smsg_event_queue ; 
 int /*<<< orphan*/  smsg_event_queue_lock ; 
 int /*<<< orphan*/  smsg_event_work ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static void smsg_app_callback(const char *from, char *msg)
{
	struct smsg_app_event *se;

	/* check if the originating z/VM user ID matches
	 * the configured sender. */
	if (sender && strlen(sender) > 0 && strcmp(from, sender) != 0)
		return;

	/* get start of message text (skip prefix and leading blanks) */
	msg += strlen(SMSG_PREFIX);
	while (*msg && isspace(*msg))
		msg++;
	if (*msg == '\0')
		return;

	/* allocate event list element and its environment */
	se = smsg_app_event_alloc(from, msg);
	if (!se)
		return;

	/* queue event and schedule work function */
	spin_lock(&smsg_event_queue_lock);
	list_add_tail(&se->list, &smsg_event_queue);
	spin_unlock(&smsg_event_queue_lock);

	schedule_work(&smsg_event_work);
	return;
}