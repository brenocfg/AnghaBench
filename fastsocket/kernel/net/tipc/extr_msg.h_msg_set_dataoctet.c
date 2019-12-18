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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 int* msg_data (struct tipc_msg*) ; 

__attribute__((used)) static inline void msg_set_dataoctet(struct tipc_msg *m, u32 pos)
{
	msg_data(m)[pos + 4] = 1;
}