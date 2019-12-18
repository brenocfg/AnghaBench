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
struct tipc_port {int conn_type; int conn_instance; } ;
struct tipc_msg {int dummy; } ;
struct msghdr {scalar_t__ msg_controllen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_TIPC ; 
#define  TIPC_CONN_MSG 130 
 int /*<<< orphan*/  TIPC_DESTNAME ; 
 int TIPC_DIRECT_MSG ; 
 int /*<<< orphan*/  TIPC_ERRINFO ; 
#define  TIPC_MCAST_MSG 129 
#define  TIPC_NAMED_MSG 128 
 int /*<<< orphan*/  TIPC_RETDATA ; 
 scalar_t__ likely (int) ; 
 int* msg_data (struct tipc_msg*) ; 
 int msg_data_sz (struct tipc_msg*) ; 
 int msg_errcode (struct tipc_msg*) ; 
 int msg_namelower (struct tipc_msg*) ; 
 int msg_nametype (struct tipc_msg*) ; 
 int msg_nameupper (struct tipc_msg*) ; 
 int msg_type (struct tipc_msg*) ; 
 int put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int anc_data_recv(struct msghdr *m, struct tipc_msg *msg,
				struct tipc_port *tport)
{
	u32 anc_data[3];
	u32 err;
	u32 dest_type;
	int has_name;
	int res;

	if (likely(m->msg_controllen == 0))
		return 0;

	/* Optionally capture errored message object(s) */

	err = msg ? msg_errcode(msg) : 0;
	if (unlikely(err)) {
		anc_data[0] = err;
		anc_data[1] = msg_data_sz(msg);
		if ((res = put_cmsg(m, SOL_TIPC, TIPC_ERRINFO, 8, anc_data)))
			return res;
		if (anc_data[1] &&
		    (res = put_cmsg(m, SOL_TIPC, TIPC_RETDATA, anc_data[1],
				    msg_data(msg))))
			return res;
	}

	/* Optionally capture message destination object */

	dest_type = msg ? msg_type(msg) : TIPC_DIRECT_MSG;
	switch (dest_type) {
	case TIPC_NAMED_MSG:
		has_name = 1;
		anc_data[0] = msg_nametype(msg);
		anc_data[1] = msg_namelower(msg);
		anc_data[2] = msg_namelower(msg);
		break;
	case TIPC_MCAST_MSG:
		has_name = 1;
		anc_data[0] = msg_nametype(msg);
		anc_data[1] = msg_namelower(msg);
		anc_data[2] = msg_nameupper(msg);
		break;
	case TIPC_CONN_MSG:
		has_name = (tport->conn_type != 0);
		anc_data[0] = tport->conn_type;
		anc_data[1] = tport->conn_instance;
		anc_data[2] = tport->conn_instance;
		break;
	default:
		has_name = 0;
	}
	if (has_name &&
	    (res = put_cmsg(m, SOL_TIPC, TIPC_DESTNAME, 12, anc_data)))
		return res;

	return 0;
}