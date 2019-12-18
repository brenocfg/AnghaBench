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

/* Variables and functions */
 int /*<<< orphan*/  BOTLIB_AI_NUM_INITIAL_CHATS ; 
 int syscall (int /*<<< orphan*/ ,int,char*) ; 

int	trap_BotNumInitialChats(int chatstate, char *type) {
	return syscall( BOTLIB_AI_NUM_INITIAL_CHATS, chatstate, type );
}