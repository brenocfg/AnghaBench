#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  UNDServerRef ;
typedef  TYPE_1__* UNDReplyRef ;
struct TYPE_6__ {int userLandNotificationKey; scalar_t__ inprogress; } ;
typedef  int /*<<< orphan*/  KUNCUserNotificationID ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_SEND_INVALID_DEST ; 
 int /*<<< orphan*/  UNDCancelNotification_rpc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UNDReply_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  UNDReply_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  UNDReply_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  UNDServer_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNDServer_reference () ; 
 TYPE_1__* UND_REPLY_NULL ; 

kern_return_t KUNCUserNotificationCancel(
	KUNCUserNotificationID id)
{
	UNDReplyRef reply = (UNDReplyRef)id;
	kern_return_t kr;
	int ulkey;

	if (reply == UND_REPLY_NULL)
		return KERN_INVALID_ARGUMENT;

	UNDReply_lock(reply);
	if (!reply->inprogress) {
		UNDReply_unlock(reply);
		return KERN_INVALID_ARGUMENT;
	}

	reply->inprogress = FALSE;
	if ((ulkey = reply->userLandNotificationKey) != 0) {
		UNDServerRef UNDServer;

		reply->userLandNotificationKey = 0;
		UNDReply_unlock(reply);

		UNDServer = UNDServer_reference();
		if (IP_VALID(UNDServer)) {
			kr = UNDCancelNotification_rpc(UNDServer,ulkey);
			UNDServer_deallocate(UNDServer);
		} else
			kr = MACH_SEND_INVALID_DEST;
	} else {
		UNDReply_unlock(reply);
		kr = KERN_SUCCESS;
	}
	UNDReply_deallocate(reply);
	return kr;
}