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
struct wlp_wss {int /*<<< orphan*/  name; int /*<<< orphan*/  virtual_addr; int /*<<< orphan*/  tag; int /*<<< orphan*/  master_key; int /*<<< orphan*/  secure_status; int /*<<< orphan*/  hash; int /*<<< orphan*/  bcast; int /*<<< orphan*/  wssid; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int scnprintf (char*,int,char*,...) ; 
 int uwb_mac_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int wlp_wss_key_print (char*,int,int /*<<< orphan*/ ) ; 
 int wlp_wss_uuid_print (char*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
ssize_t __wlp_wss_properties_show(struct wlp_wss *wss, char *buf,
				  size_t bufsize)
{
	ssize_t result;

	result = wlp_wss_uuid_print(buf, bufsize, &wss->wssid);
	result += scnprintf(buf + result, bufsize - result, " ");
	result += uwb_mac_addr_print(buf + result, bufsize - result,
				     &wss->bcast);
	result += scnprintf(buf + result, bufsize - result,
			    " 0x%02x %u ", wss->hash, wss->secure_status);
	result += wlp_wss_key_print(buf + result, bufsize - result,
				    wss->master_key);
	result += scnprintf(buf + result, bufsize - result, " 0x%02x ",
			    wss->tag);
	result += uwb_mac_addr_print(buf + result, bufsize - result,
				     &wss->virtual_addr);
	result += scnprintf(buf + result, bufsize - result, " %s", wss->name);
	result += scnprintf(buf + result, bufsize - result,
			    "\n\n#WSSID\n#WSS broadcast address\n"
			    "#WSS hash\n#WSS secure status\n"
			    "#WSS master key\n#WSS local tag\n"
			    "#WSS local virtual EUI-48\n#WSS name\n");
	return result;
}