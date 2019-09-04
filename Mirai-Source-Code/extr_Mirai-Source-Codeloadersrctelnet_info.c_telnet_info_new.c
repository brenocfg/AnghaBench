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
struct telnet_info {int has_auth; int /*<<< orphan*/  has_arch; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  arch; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  port_t ;
typedef  int /*<<< orphan*/  ipv4_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

struct telnet_info *telnet_info_new(char *user, char *pass, char *arch, ipv4_t addr, port_t port, struct telnet_info *info)
{
    if (user != NULL)
        strcpy(info->user, user);
    if (pass != NULL)
        strcpy(info->pass, pass);
    if (arch != NULL)
        strcpy(info->arch, arch);
    info->addr = addr;
    info->port = port;

    info->has_auth = user != NULL || pass != NULL;
    info->has_arch = arch != NULL;

    return info;
}