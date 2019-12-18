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
struct telnet_info {int dummy; } ;
typedef  int /*<<< orphan*/  port_t ;
typedef  int /*<<< orphan*/  ipv4_t ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 
 struct telnet_info* telnet_info_new (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct telnet_info*) ; 

struct telnet_info *telnet_info_parse(char *str, struct telnet_info *out) // Format: ip:port user:pass arch
{
    char *conn, *auth, *arch;
    char *addr_str, *port_str, *user = NULL, *pass = NULL;
    ipv4_t addr;
    port_t port;

    if ((conn = strtok(str, " ")) == NULL)
        return NULL;
    if ((auth = strtok(NULL, " ")) == NULL)
        return NULL;
    arch = strtok(NULL, " "); // We don't care if we don't know the arch

    if ((addr_str = strtok(conn, ":")) == NULL)
        return NULL;
    if ((port_str = strtok(NULL, ":")) == NULL)
        return NULL;

    if (strlen(auth) == 1)
    {
        if (auth[0] == ':')
        {
            user = "";
            pass = "";
        }
        else if (auth[0] != '?')
            return NULL;
    }
    else
    {
        user = strtok(auth, ":");
        pass = strtok(NULL, ":");
    }

    addr = inet_addr(addr_str);
    port = htons(atoi(port_str));

    return telnet_info_new(user, pass, arch, addr, port, out);
}