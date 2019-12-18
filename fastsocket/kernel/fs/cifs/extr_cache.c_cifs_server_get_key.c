#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
struct cifs_server_key {int family; TYPE_1__* addr; int /*<<< orphan*/  port; } ;
struct TCP_Server_Info {int /*<<< orphan*/  dstaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipv6_addr; int /*<<< orphan*/  ipv4_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  cERROR (int,char*,int) ; 
 int /*<<< orphan*/  memset (struct cifs_server_key*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t cifs_server_get_key(const void *cookie_netfs_data,
				   void *buffer, uint16_t maxbuf)
{
	const struct TCP_Server_Info *server = cookie_netfs_data;
	const struct sockaddr *sa = (struct sockaddr *) &server->dstaddr;
	const struct sockaddr_in *addr = (struct sockaddr_in *) sa;
	const struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *) sa;
	struct cifs_server_key *key = buffer;
	uint16_t key_len = sizeof(struct cifs_server_key);

	memset(key, 0, key_len);

	/*
	 * Should not be a problem as sin_family/sin6_family overlays
	 * sa_family field
	 */
	switch (sa->sa_family) {
	case AF_INET:
		key->family = sa->sa_family;
		key->port = addr->sin_port;
		key->addr[0].ipv4_addr = addr->sin_addr;
		key_len += sizeof(key->addr[0].ipv4_addr);
		break;

	case AF_INET6:
		key->family = sa->sa_family;
		key->port = addr6->sin6_port;
		key->addr[0].ipv6_addr = addr6->sin6_addr;
		key_len += sizeof(key->addr[0].ipv6_addr);
		break;

	default:
		cERROR(1, "Unknown network family '%d'", sa->sa_family);
		key_len = 0;
		break;
	}

	return key_len;
}