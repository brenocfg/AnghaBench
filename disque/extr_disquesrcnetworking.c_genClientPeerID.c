#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ip ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ client ;
struct TYPE_5__ {char* unixsocket; } ;

/* Variables and functions */
 int CLIENT_UNIX_SOCKET ; 
 int C_ERR ; 
 int C_OK ; 
 int NET_IP_STR_LEN ; 
 int anetPeerToString (int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  formatPeerID (char*,size_t,char*,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

int genClientPeerID(client *client, char *peerid, size_t peerid_len) {
    char ip[NET_IP_STR_LEN];
    int port;

    if (client->flags & CLIENT_UNIX_SOCKET) {
        /* Unix socket client. */
        snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
        return C_OK;
    } else {
        /* TCP client. */
        int retval = anetPeerToString(client->fd,ip,sizeof(ip),&port);
        formatPeerID(peerid,peerid_len,ip,port);
        return (retval == -1) ? C_ERR : C_OK;
    }
}