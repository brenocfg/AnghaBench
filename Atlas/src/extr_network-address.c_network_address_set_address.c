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
typedef  int /*<<< orphan*/  network_address ;
typedef  int guint ;
typedef  int gint ;
typedef  char gchar ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ *,int) ; 
 char* g_strndup (char const*,int) ; 
 int network_address_set_address_ip (int /*<<< orphan*/ *,char const*,int) ; 
 int network_address_set_address_un (int /*<<< orphan*/ *,char const*) ; 
 char* strchr (char const*,char) ; 
 int strtoul (char*,char**,int) ; 

gint network_address_set_address(network_address *addr, const gchar *address) {
	gchar *s;

	g_return_val_if_fail(addr, -1);

	/* split the address:port */
	if (address[0] == '/')
		return network_address_set_address_un(addr, address);
	
	if (NULL != (s = strchr(address, ':'))) {
		gint ret;
		char *ip_address = g_strndup(address, s - address); /* may be NULL for strdup(..., 0) */
		char *port_err = NULL;

		guint port = strtoul(s + 1, &port_err, 10);

		if (*(s + 1) == '\0') {
			g_critical("%s: IP-address has to be in the form [<ip>][:<port>], is '%s'. No port number",
					G_STRLOC, address);
			ret = -1;
		} else if (*port_err != '\0') {
			g_critical("%s: IP-address has to be in the form [<ip>][:<port>], is '%s'. Failed to parse the port at '%s'",
					G_STRLOC, address, port_err);
			ret = -1;
		} else {
			ret = network_address_set_address_ip(addr, ip_address, port);
		}

		if (ip_address) g_free(ip_address);

		return ret;
	}
	/* perhaps it is a plain IP address, lets add the default-port */
	return network_address_set_address_ip(addr, address, 3306);
}