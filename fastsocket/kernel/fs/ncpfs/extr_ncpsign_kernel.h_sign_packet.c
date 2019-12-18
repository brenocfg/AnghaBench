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
struct ncp_server {scalar_t__ sign_active; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __sign_packet (struct ncp_server*,char const*,size_t,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline size_t sign_packet(struct ncp_server *server, const char *data, size_t size, __u32 totalsize, void *sign_buff) {
#ifdef CONFIG_NCPFS_PACKET_SIGNING
	if (server->sign_active) {
		__sign_packet(server, data, size, totalsize, sign_buff);
		return 8;
	}
#endif
	return 0;
}