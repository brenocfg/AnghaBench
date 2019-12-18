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
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ msg_data (struct tipc_msg*) ; 

__attribute__((used)) static inline struct tipc_msg *msg_get_wrapped(struct tipc_msg *m)
{
	return (struct tipc_msg *)msg_data(m);
}