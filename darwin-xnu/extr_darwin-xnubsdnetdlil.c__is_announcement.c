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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static __inline__ int
_is_announcement(const struct sockaddr_in * sender_sin,
    const struct sockaddr_in * target_sin)
{
	if (sender_sin == NULL) {
		return (FALSE);
	}
	return (sender_sin->sin_addr.s_addr == target_sin->sin_addr.s_addr);
}