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

/* Variables and functions */
 int /*<<< orphan*/  RDS_INFO_CONNECTIONS ; 
 int /*<<< orphan*/  RDS_INFO_RETRANS_MESSAGES ; 
 int /*<<< orphan*/  RDS_INFO_SEND_MESSAGES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_conn_hash ; 
 int /*<<< orphan*/  rds_conn_info ; 
 int /*<<< orphan*/  rds_conn_message_info_retrans ; 
 int /*<<< orphan*/  rds_conn_message_info_send ; 
 int /*<<< orphan*/  rds_conn_slab ; 
 int /*<<< orphan*/  rds_info_deregister_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_loop_exit () ; 

void rds_conn_exit(void)
{
	rds_loop_exit();

	WARN_ON(!hlist_empty(rds_conn_hash));

	kmem_cache_destroy(rds_conn_slab);

	rds_info_deregister_func(RDS_INFO_CONNECTIONS, rds_conn_info);
	rds_info_deregister_func(RDS_INFO_SEND_MESSAGES,
				 rds_conn_message_info_send);
	rds_info_deregister_func(RDS_INFO_RETRANS_MESSAGES,
				 rds_conn_message_info_retrans);
}