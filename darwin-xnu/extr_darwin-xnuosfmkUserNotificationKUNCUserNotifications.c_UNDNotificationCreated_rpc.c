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
typedef  TYPE_1__* UNDReplyRef ;
struct TYPE_6__ {int userLandNotificationKey; scalar_t__ inprogress; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  UNDReply_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  UNDReply_unlock (TYPE_1__*) ; 
 TYPE_1__* UND_REPLY_NULL ; 

kern_return_t
UNDNotificationCreated_rpc (
        UNDReplyRef	reply,
        int		userLandNotificationKey)
{
	if (reply == UND_REPLY_NULL)
		return KERN_INVALID_ARGUMENT;

	UNDReply_lock(reply);
	if (reply->inprogress || reply->userLandNotificationKey != -1) {
		UNDReply_unlock(reply);
		return KERN_INVALID_ARGUMENT;
	}
	reply->userLandNotificationKey = userLandNotificationKey;
	UNDReply_unlock(reply);
	return KERN_SUCCESS;
}