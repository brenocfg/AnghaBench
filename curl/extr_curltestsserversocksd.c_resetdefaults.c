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
struct TYPE_2__ {int /*<<< orphan*/  password; int /*<<< orphan*/  user; int /*<<< orphan*/  addr; int /*<<< orphan*/  port; int /*<<< orphan*/  connectrep; int /*<<< orphan*/  reqcmd; int /*<<< orphan*/  responsemethod; int /*<<< orphan*/  responseversion; int /*<<< orphan*/  nmethods_max; int /*<<< orphan*/  nmethods_min; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 char* CONFIG_ADDR ; 
 int /*<<< orphan*/  CONFIG_CONNECTREP ; 
 int /*<<< orphan*/  CONFIG_NMETHODS_MAX ; 
 int /*<<< orphan*/  CONFIG_NMETHODS_MIN ; 
 int /*<<< orphan*/  CONFIG_PORT ; 
 int /*<<< orphan*/  CONFIG_REQCMD ; 
 int /*<<< orphan*/  CONFIG_RESPONSEMETHOD ; 
 int /*<<< orphan*/  CONFIG_RESPONSEVERSION ; 
 int /*<<< orphan*/  CONFIG_VERSION ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  logmsg (char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void resetdefaults(void)
{
  logmsg("Reset to defaults");
  config.version = CONFIG_VERSION;
  config.nmethods_min = CONFIG_NMETHODS_MIN;
  config.nmethods_max = CONFIG_NMETHODS_MAX;
  config.responseversion = CONFIG_RESPONSEVERSION;
  config.responsemethod = CONFIG_RESPONSEMETHOD;
  config.reqcmd = CONFIG_REQCMD;
  config.connectrep = CONFIG_CONNECTREP;
  config.port = CONFIG_PORT;
  strcpy(config.addr, CONFIG_ADDR);
  strcpy(config.user, "user");
  strcpy(config.password, "password");
}