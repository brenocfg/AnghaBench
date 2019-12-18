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
struct tipc_media_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,struct tipc_media_addr*,int) ; 

__attribute__((used)) static inline void msg_set_media_addr(struct tipc_msg *m, struct tipc_media_addr *a)
{
	memcpy(&((int *)m)[5], a, sizeof(*a));
}