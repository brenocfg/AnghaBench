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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct capi_notifier {unsigned int cmd; int /*<<< orphan*/  work; void* ncci; int /*<<< orphan*/  applid; void* controller; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct capi_notifier* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_handler ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int notify_push(unsigned int cmd, u32 controller, u16 applid, u32 ncci)
{
	struct capi_notifier *np = kmalloc(sizeof(*np), GFP_ATOMIC);

	if (!np)
		return -ENOMEM;

	INIT_WORK(&np->work, notify_handler);
	np->cmd = cmd;
	np->controller = controller;
	np->applid = applid;
	np->ncci = ncci;

	schedule_work(&np->work);
	return 0;
}