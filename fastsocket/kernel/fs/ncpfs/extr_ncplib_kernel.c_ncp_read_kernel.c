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
struct ncp_server {int dummy; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ncp_add_be16 (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_be32 (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_mem (struct ncp_server*,char const*,int) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int ncp_reply_be16 (struct ncp_server*,int /*<<< orphan*/ ) ; 
 char* ncp_reply_data (struct ncp_server*,int) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int
ncp_read_kernel(struct ncp_server *server, const char *file_id,
	     __u32 offset, __u16 to_read, char *target, int *bytes_read)
{
	char *source;
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 0);
	ncp_add_mem(server, file_id, 6);
	ncp_add_be32(server, offset);
	ncp_add_be16(server, to_read);

	if ((result = ncp_request(server, 72)) != 0) {
		goto out;
	}
	*bytes_read = ncp_reply_be16(server, 0);
	source = ncp_reply_data(server, 2 + (offset & 1));

	memcpy(target, source, *bytes_read);
out:
	ncp_unlock_server(server);
	return result;
}