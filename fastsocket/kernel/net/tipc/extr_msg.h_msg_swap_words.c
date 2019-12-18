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
typedef  size_t u32 ;
struct tipc_msg {size_t* hdr; } ;

/* Variables and functions */

__attribute__((used)) static inline void msg_swap_words(struct tipc_msg *msg, u32 a, u32 b)
{
	u32 temp = msg->hdr[a];

	msg->hdr[a] = msg->hdr[b];
	msg->hdr[b] = temp;
}