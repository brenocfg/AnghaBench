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
struct bcom_task {unsigned int bd_size; scalar_t__ bd; } ;
typedef  void bcom_bd ;

/* Variables and functions */

__attribute__((used)) static inline struct bcom_bd
*bcom_get_bd(struct bcom_task *tsk, unsigned int index)
{
	/* A cast to (void*) so the address can be incremented by the
	 * real size instead of by sizeof(struct bcom_bd) */
	return ((void *)tsk->bd) + (index * tsk->bd_size);
}