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
struct TYPE_2__ {int tail; } ;
struct ocrdma_eq {TYPE_1__ q; } ;

/* Variables and functions */
 int OCRDMA_EQ_LEN ; 

__attribute__((used)) static inline void ocrdma_eq_inc_tail(struct ocrdma_eq *eq)
{
	eq->q.tail = (eq->q.tail + 1) & (OCRDMA_EQ_LEN - 1);
}