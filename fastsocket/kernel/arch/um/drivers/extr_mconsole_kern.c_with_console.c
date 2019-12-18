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
struct mconsole_output {int /*<<< orphan*/  list; struct mc_request* req; } ;
struct mc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_lock ; 
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mconsole_reply_len (struct mc_request*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void stub1 (void*) ; 

__attribute__((used)) static void with_console(struct mc_request *req, void (*proc)(void *),
			 void *arg)
{
	struct mconsole_output entry;
	unsigned long flags;

	entry.req = req;
	spin_lock_irqsave(&client_lock, flags);
	list_add(&entry.list, &clients);
	spin_unlock_irqrestore(&client_lock, flags);

	(*proc)(arg);

	mconsole_reply_len(req, "", 0, 0, 0);

	spin_lock_irqsave(&client_lock, flags);
	list_del(&entry.list);
	spin_unlock_irqrestore(&client_lock, flags);
}