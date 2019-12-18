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
struct socket {int dummy; } ;
struct rds_info_lengths {int dummy; } ;
struct rds_info_iterator {int dummy; } ;
struct rds_info_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_conn_info_visitor ; 
 int /*<<< orphan*/  rds_for_each_conn_info (struct socket*,unsigned int,struct rds_info_iterator*,struct rds_info_lengths*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rds_conn_info(struct socket *sock, unsigned int len,
			  struct rds_info_iterator *iter,
			  struct rds_info_lengths *lens)
{
	rds_for_each_conn_info(sock, len, iter, lens,
				rds_conn_info_visitor,
				sizeof(struct rds_info_connection));
}