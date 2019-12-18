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
struct ipz_queue {int dummy; } ;

/* Variables and functions */
 void* ipz_qeit_get_inc (struct ipz_queue*) ; 
 scalar_t__ ipz_qeit_is_valid (struct ipz_queue*) ; 

__attribute__((used)) static inline void *ipz_qeit_get_inc_valid(struct ipz_queue *queue)
{
	return ipz_qeit_is_valid(queue) ? ipz_qeit_get_inc(queue) : NULL;
}