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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
#define  SIOCATMARK 143 
#define  SIOCGASSOCIDS32 142 
#define  SIOCGASSOCIDS64 141 
#define  SIOCGCONNIDS32 140 
#define  SIOCGCONNIDS64 139 
#define  SIOCGCONNINFO32 138 
#define  SIOCGCONNINFO64 137 
#define  SIOCGCONNORDER 136 
#define  SIOCGHIWAT 135 
#define  SIOCGLOWAT 134 
#define  SIOCGPGRP 133 
#define  SIOCSCONNORDER 132 
#define  SIOCSETOT 131 
#define  SIOCSHIWAT 130 
#define  SIOCSLOWAT 129 
#define  SIOCSPGRP 128 

__attribute__((used)) static __attribute__((unused)) void
soioctl_cassert(void)
{
	/*
	 * This is equivalent to _CASSERT() and the compiler wouldn't
	 * generate any instructions, thus for compile time only.
	 */
	switch ((u_long)0) {
	case 0:

	/* bsd/sys/sockio.h */
	case SIOCSHIWAT:
	case SIOCGHIWAT:
	case SIOCSLOWAT:
	case SIOCGLOWAT:
	case SIOCATMARK:
	case SIOCSPGRP:
	case SIOCGPGRP:
	case SIOCSETOT:
	case SIOCGASSOCIDS32:
	case SIOCGASSOCIDS64:
	case SIOCGCONNIDS32:
	case SIOCGCONNIDS64:
	case SIOCGCONNINFO32:
	case SIOCGCONNINFO64:
	case SIOCSCONNORDER:
	case SIOCGCONNORDER:
		;
	}
}