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
struct rds_sock {int dummy; } ;
struct TYPE_2__ {int sk_rcvbuf; } ;

/* Variables and functions */
 TYPE_1__* rds_rs_to_sk (struct rds_sock*) ; 

__attribute__((used)) static inline int rds_sk_rcvbuf(struct rds_sock *rs)
{
	return rds_rs_to_sk(rs)->sk_rcvbuf / 2;
}