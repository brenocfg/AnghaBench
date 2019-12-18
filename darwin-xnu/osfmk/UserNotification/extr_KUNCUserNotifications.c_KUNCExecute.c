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
 int /*<<< orphan*/  UNDExecute_rpc (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  UNDServer_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNDServer_reference () ; 

kern_return_t KUNCExecute(char executionPath[1024], int uid, int gid)
{

	UNDServerRef UNDServer;

	UNDServer = UNDServer_reference();
	if (IP_VALID(UNDServer)) {
		kern_return_t kr;
		kr = UNDExecute_rpc(UNDServer, executionPath, uid, gid);
		UNDServer_deallocate(UNDServer);
		return kr;
	}
	return MACH_SEND_INVALID_DEST;
}