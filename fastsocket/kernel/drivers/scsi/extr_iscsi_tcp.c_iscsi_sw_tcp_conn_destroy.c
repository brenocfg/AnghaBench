#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct TYPE_4__ {scalar_t__ tfm; } ;
struct TYPE_3__ {scalar_t__ tfm; } ;
struct iscsi_sw_tcp_conn {TYPE_2__ rx_hash; TYPE_1__ tx_hash; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_hash (scalar_t__) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_release_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_tcp_conn_teardown (struct iscsi_cls_conn*) ; 

__attribute__((used)) static void iscsi_sw_tcp_conn_destroy(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	iscsi_sw_tcp_release_conn(conn);

	if (tcp_sw_conn->tx_hash.tfm)
		crypto_free_hash(tcp_sw_conn->tx_hash.tfm);
	if (tcp_sw_conn->rx_hash.tfm)
		crypto_free_hash(tcp_sw_conn->rx_hash.tfm);

	iscsi_tcp_conn_teardown(cls_conn);
}