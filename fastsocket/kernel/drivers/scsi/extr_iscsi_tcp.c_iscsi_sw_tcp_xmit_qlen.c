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
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_segment {int total_copied; int total_size; } ;
struct TYPE_2__ {struct iscsi_segment segment; } ;
struct iscsi_sw_tcp_conn {TYPE_1__ out; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;

/* Variables and functions */

__attribute__((used)) static inline int iscsi_sw_tcp_xmit_qlen(struct iscsi_conn *conn)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	struct iscsi_segment *segment = &tcp_sw_conn->out.segment;

	return segment->total_copied - segment->total_size;
}