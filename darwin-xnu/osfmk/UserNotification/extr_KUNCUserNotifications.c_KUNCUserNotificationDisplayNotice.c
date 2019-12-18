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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  UNDServerRef ;

/* Variables and functions */
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_SEND_INVALID_DEST ; 
 int /*<<< orphan*/  UNDDisplayNoticeSimple_rpc (int /*<<< orphan*/ ,int,unsigned int,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  UNDServer_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNDServer_reference () ; 

kern_return_t
KUNCUserNotificationDisplayNotice(
	int		noticeTimeout,
	unsigned	flags,
	char		*iconPath,
	char		*soundPath,
	char		*localizationPath,
	char		*alertHeader,
	char		*alertMessage,
	char		*defaultButtonTitle)
{
	UNDServerRef UNDServer;

	UNDServer = UNDServer_reference();
	if (IP_VALID(UNDServer)) {
		kern_return_t kr;
		kr = UNDDisplayNoticeSimple_rpc(UNDServer,
					noticeTimeout,
					flags,
					iconPath,
					soundPath,
					localizationPath,
					alertHeader,
					alertMessage,
					defaultButtonTitle);
		UNDServer_deallocate(UNDServer);
		return kr;
	}
	return MACH_SEND_INVALID_DEST;
}