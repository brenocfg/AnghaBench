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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u32 ;
struct rds_message {scalar_t__ m_ack_seq; int /*<<< orphan*/  m_flags; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_MSG_HAS_ACK_SEQ ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_tcp_is_acked(struct rds_message *rm, uint64_t ack)
{
	if (!test_bit(RDS_MSG_HAS_ACK_SEQ, &rm->m_flags))
		return 0;
	return (__s32)((u32)rm->m_ack_seq - (u32)ack) < 0;
}