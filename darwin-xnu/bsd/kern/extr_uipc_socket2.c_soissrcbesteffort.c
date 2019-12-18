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
struct socket {scalar_t__ so_traffic_class; } ;

/* Variables and functions */
 scalar_t__ SO_TC_BE ; 
 scalar_t__ SO_TC_OAM ; 
 scalar_t__ SO_TC_RD ; 

inline int
soissrcbesteffort(struct socket *so)
{
	return (so->so_traffic_class == SO_TC_BE ||
	    so->so_traffic_class == SO_TC_RD ||
	    so->so_traffic_class == SO_TC_OAM);
}