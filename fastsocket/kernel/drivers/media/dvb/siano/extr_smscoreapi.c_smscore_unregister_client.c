#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ next; } ;
struct smscore_idlist_t {int /*<<< orphan*/  entry; int /*<<< orphan*/  context; TYPE_1__ idlist; struct smscore_device_t* coredev; } ;
struct smscore_device_t {int /*<<< orphan*/  clientslock; } ;
struct smscore_client_t {int /*<<< orphan*/  entry; int /*<<< orphan*/  context; TYPE_1__ idlist; struct smscore_device_t* coredev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smscore_idlist_t*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  sms_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void smscore_unregister_client(struct smscore_client_t *client)
{
	struct smscore_device_t *coredev = client->coredev;
	unsigned long flags;

	spin_lock_irqsave(&coredev->clientslock, flags);


	while (!list_empty(&client->idlist)) {
		struct smscore_idlist_t *identry =
			(struct smscore_idlist_t *) client->idlist.next;
		list_del(&identry->entry);
		kfree(identry);
	}

	sms_info("%p", client->context);

	list_del(&client->entry);
	kfree(client);

	spin_unlock_irqrestore(&coredev->clientslock, flags);
}