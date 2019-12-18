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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 scalar_t__ ncp_reply_data (struct ncp_server*,int) ; 

__attribute__((used)) static __le32
ncp_reply_dword(struct ncp_server *server, int offset)
{
	return get_unaligned((__le32 *)ncp_reply_data(server, offset));
}