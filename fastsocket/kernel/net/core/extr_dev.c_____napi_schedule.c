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
struct softnet_data {int /*<<< orphan*/  poll_list; } ;
struct napi_struct {int /*<<< orphan*/  poll_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_RX_SOFTIRQ ; 
 int /*<<< orphan*/  __raise_softirq_irqoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ____napi_schedule(struct softnet_data *sd,
					struct napi_struct *napi)
{
	list_add_tail(&napi->poll_list, &sd->poll_list);
	__raise_softirq_irqoff(NET_RX_SOFTIRQ);
}