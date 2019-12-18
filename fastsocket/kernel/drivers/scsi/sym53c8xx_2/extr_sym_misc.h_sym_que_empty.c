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
struct sym_quehead {struct sym_quehead* flink; } ;

/* Variables and functions */

__attribute__((used)) static inline int sym_que_empty(struct sym_quehead *head)
{
	return head->flink == head;
}