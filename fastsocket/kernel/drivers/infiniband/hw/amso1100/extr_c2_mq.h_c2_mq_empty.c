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
struct c2_mq {scalar_t__ priv; int /*<<< orphan*/ * shared; } ;

/* Variables and functions */
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int c2_mq_empty(struct c2_mq *q)
{
	return q->priv == be16_to_cpu(*q->shared);
}