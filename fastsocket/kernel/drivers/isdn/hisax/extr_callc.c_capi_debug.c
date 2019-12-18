#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct Channel {int /*<<< orphan*/  chan; int /*<<< orphan*/  cs; } ;
struct TYPE_3__ {int Length; } ;
typedef  TYPE_1__ capi_msg ;

/* Variables and functions */
 int /*<<< orphan*/  HiSax_putstatus (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 char* tmpbuf ; 

__attribute__((used)) static void
capi_debug(struct Channel *chanp, capi_msg *cm)
{
	char *t = tmpbuf;

	t += QuickHex(t, (u_char *)cm, (cm->Length>50)? 50: cm->Length);
	t--;
	*t= 0;
	HiSax_putstatus(chanp->cs, "Ch", "%d CAPIMSG %s", chanp->chan, tmpbuf);
}