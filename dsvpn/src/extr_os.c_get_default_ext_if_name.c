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
 char const* read_from_shell_command (char*,int,char*) ; 

const char *get_default_ext_if_name(void)
{
    static char if_name[64];
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || \
    defined(__DragonFly__) || defined(__NetBSD__)
    return read_from_shell_command(if_name, sizeof if_name,
                                   "route -n get default 2>/dev/null|awk "
                                   "'/interface:/{print $2;exit}'");
#elif defined(__linux__)
    return read_from_shell_command(if_name, sizeof if_name,
                                   "ip route show default 2>/dev/null|awk '/default/{print $5}'");
#else
    return NULL;
#endif
}