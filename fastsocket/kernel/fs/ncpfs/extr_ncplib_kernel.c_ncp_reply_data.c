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
struct ncp_server {char* packet; } ;
struct ncp_reply_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline char *
ncp_reply_data(struct ncp_server *server, int offset)
{
	return &(server->packet[sizeof(struct ncp_reply_header) + offset]);
}