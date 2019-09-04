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
typedef  char* sds ;

/* Variables and functions */
 char* cliVersion () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 

__attribute__((used)) static void cliOutputGenericHelp(void) {
    sds version = cliVersion();
    printf(
        "disque %s\r\n"
        "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
        "      \"help <command>\" for help on <command>\r\n"
        "      \"help <tab>\" to get a list of possible help topics\r\n"
        "      \"quit\" to exit\r\n",
        version
    );
    sdsfree(version);
}