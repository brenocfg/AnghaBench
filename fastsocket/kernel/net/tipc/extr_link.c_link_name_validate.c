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
struct link_name {int /*<<< orphan*/  if_peer; void* addr_peer; int /*<<< orphan*/  if_local; void* addr_local; } ;

/* Variables and functions */
 int TIPC_MAX_IF_NAME ; 
 int TIPC_MAX_LINK_NAME ; 
 int sscanf (char*,char*,int*,int*,int*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int strspn (char*,int /*<<< orphan*/ ) ; 
 void* tipc_addr (int,int,int) ; 
 int /*<<< orphan*/  tipc_alphabet ; 

__attribute__((used)) static int link_name_validate(const char *name, struct link_name *name_parts)
{
	char name_copy[TIPC_MAX_LINK_NAME];
	char *addr_local;
	char *if_local;
	char *addr_peer;
	char *if_peer;
	char dummy;
	u32 z_local, c_local, n_local;
	u32 z_peer, c_peer, n_peer;
	u32 if_local_len;
	u32 if_peer_len;

	/* copy link name & ensure length is OK */

	name_copy[TIPC_MAX_LINK_NAME - 1] = 0;
	/* need above in case non-Posix strncpy() doesn't pad with nulls */
	strncpy(name_copy, name, TIPC_MAX_LINK_NAME);
	if (name_copy[TIPC_MAX_LINK_NAME - 1] != 0)
		return 0;

	/* ensure all component parts of link name are present */

	addr_local = name_copy;
	if ((if_local = strchr(addr_local, ':')) == NULL)
		return 0;
	*(if_local++) = 0;
	if ((addr_peer = strchr(if_local, '-')) == NULL)
		return 0;
	*(addr_peer++) = 0;
	if_local_len = addr_peer - if_local;
	if ((if_peer = strchr(addr_peer, ':')) == NULL)
		return 0;
	*(if_peer++) = 0;
	if_peer_len = strlen(if_peer) + 1;

	/* validate component parts of link name */

	if ((sscanf(addr_local, "%u.%u.%u%c",
		    &z_local, &c_local, &n_local, &dummy) != 3) ||
	    (sscanf(addr_peer, "%u.%u.%u%c",
		    &z_peer, &c_peer, &n_peer, &dummy) != 3) ||
	    (z_local > 255) || (c_local > 4095) || (n_local > 4095) ||
	    (z_peer  > 255) || (c_peer  > 4095) || (n_peer  > 4095) ||
	    (if_local_len <= 1) || (if_local_len > TIPC_MAX_IF_NAME) ||
	    (if_peer_len  <= 1) || (if_peer_len  > TIPC_MAX_IF_NAME) ||
	    (strspn(if_local, tipc_alphabet) != (if_local_len - 1)) ||
	    (strspn(if_peer, tipc_alphabet) != (if_peer_len - 1)))
		return 0;

	/* return link name components, if necessary */

	if (name_parts) {
		name_parts->addr_local = tipc_addr(z_local, c_local, n_local);
		strcpy(name_parts->if_local, if_local);
		name_parts->addr_peer = tipc_addr(z_peer, c_peer, n_peer);
		strcpy(name_parts->if_peer, if_peer);
	}
	return 1;
}