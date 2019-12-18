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
struct dhcp {int dummy; } ;
typedef  int /*<<< orphan*/  dhcpol_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTP_RESPONSE ; 
 int /*<<< orphan*/  BSDP_RESPONSE ; 
 int /*<<< orphan*/  FALSE ; 
 void* IOBSDRegistryEntryForDeviceTree (char*) ; 
 void* IOBSDRegistryEntryGetData (void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IOBSDRegistryEntryRelease (void*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ dhcpol_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dhcpol_parse_packet (int /*<<< orphan*/ *,struct dhcp const*,int) ; 
 int /*<<< orphan*/  dhcptag_root_path_e ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static boolean_t
get_root_path(char * root_path)
{
    void *		entry;
    boolean_t		found = FALSE;
    const void *	pkt;
    int			pkt_len;
    
    entry = IOBSDRegistryEntryForDeviceTree("/chosen");
    if (entry == NULL) {
	return (FALSE);
    }
    pkt = IOBSDRegistryEntryGetData(entry, BSDP_RESPONSE, &pkt_len);
    if (pkt != NULL && pkt_len >= (int)sizeof(struct dhcp)) {
	printf("netboot: retrieving root path from BSDP response\n");
    }
    else {
	pkt = IOBSDRegistryEntryGetData(entry, BOOTP_RESPONSE, 
					&pkt_len);
	if (pkt != NULL && pkt_len >= (int)sizeof(struct dhcp)) {
	    printf("netboot: retrieving root path from BOOTP response\n");
	}
    }
    if (pkt != NULL) {
	int			len;
	dhcpol_t 		options;
	const char *		path;
	const struct dhcp *	reply;

	reply = (const struct dhcp *)pkt;
	(void)dhcpol_parse_packet(&options, reply, pkt_len);

	path = (const char *)dhcpol_find(&options, 
					 dhcptag_root_path_e, &len, NULL);
	if (path) {
	    memcpy(root_path, path, len);
	    root_path[len] = '\0';
	    found = TRUE;
	}
    }
    IOBSDRegistryEntryRelease(entry);
    return (found);

}