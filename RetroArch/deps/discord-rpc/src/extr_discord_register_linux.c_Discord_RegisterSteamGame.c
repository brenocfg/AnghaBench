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
 int /*<<< orphan*/  Discord_Register (char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

void Discord_RegisterSteamGame(
      const char* applicationId,
      const char* steamId)
{
   char command[256];
   sprintf(command, "xdg-open steam://rungameid/%s", steamId);
   Discord_Register(applicationId, command);
}