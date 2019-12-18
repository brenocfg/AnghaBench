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
struct ncp_reply_header {int conn_low; int conn_high; } ;

/* Variables and functions */

__attribute__((used)) static inline int get_conn_number(struct ncp_reply_header *rp)
{
	return rp->conn_low | (rp->conn_high << 8);
}