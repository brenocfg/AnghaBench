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
struct cryptocop_session {scalar_t__ sid; struct cryptocop_session* next; } ;
typedef  scalar_t__ cryptocop_session_id ;

/* Variables and functions */
 struct cryptocop_session* cryptocop_sessions ; 
 int /*<<< orphan*/  cryptocop_sessions_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct cryptocop_session *get_session(cryptocop_session_id sid)
{
	struct cryptocop_session    *sess;
	unsigned long int           flags;

	spin_lock_irqsave(&cryptocop_sessions_lock, flags);
	sess = cryptocop_sessions;
	while (sess && (sess->sid != sid)){
		sess = sess->next;
	}
	spin_unlock_irqrestore(&cryptocop_sessions_lock, flags);

	return sess;
}