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
typedef  int u32 ;
struct netconn {int socket; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETCONN_RAW ; 
 int /*<<< orphan*/  NETCONN_TCP ; 
 int /*<<< orphan*/  NETCONN_UDP ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_STREAM 128 
 int alloc_socket (struct netconn*) ; 
 int /*<<< orphan*/  evt_callback ; 
 int /*<<< orphan*/  netconn_delete (struct netconn*) ; 
 struct netconn* netconn_new_with_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netconn* netconn_new_with_proto_and_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

s32 net_socket(u32 domain,u32 type,u32 protocol)
{
	s32 i;
	struct netconn *conn;

	switch(type) {
		case SOCK_RAW:
			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_socket(SOCK_RAW)\n"));
			conn = netconn_new_with_proto_and_callback(NETCONN_RAW,protocol,evt_callback);
			break;
		case SOCK_DGRAM:
			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_socket(SOCK_DGRAM)\n"));
			conn = netconn_new_with_callback(NETCONN_UDP,evt_callback);
			break;
		case SOCK_STREAM:
			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_socket(SOCK_STREAM)\n"));
			conn = netconn_new_with_callback(NETCONN_TCP,evt_callback);
			break;
		default:
			return -1;
	}
	if(!conn) return -1;

	i = alloc_socket(conn);
	if(i==-1) {
		netconn_delete(conn);
		return -1;
	}

	conn->socket = i;
	return i;
}