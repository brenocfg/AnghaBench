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
struct socket {int so_flags1; } ;

/* Variables and functions */
 int SOF1_TRAFFIC_MGT_SO_BACKGROUND ; 

inline int
soisthrottled(struct socket *so)
{
	return (so->so_flags1 & SOF1_TRAFFIC_MGT_SO_BACKGROUND);
}