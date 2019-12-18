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
typedef  int /*<<< orphan*/  userinfo ;
struct TYPE_3__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClientUserinfoChanged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,char*) ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  trap_GetUserinfo (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_SetUserinfo (int /*<<< orphan*/ ,char*) ; 

void BotSetUserInfo(bot_state_t *bs, char *key, char *value) {
	char userinfo[MAX_INFO_STRING];

	trap_GetUserinfo(bs->client, userinfo, sizeof(userinfo));
	Info_SetValueForKey(userinfo, key, value);
	trap_SetUserinfo(bs->client, userinfo);
	ClientUserinfoChanged( bs->client );
}