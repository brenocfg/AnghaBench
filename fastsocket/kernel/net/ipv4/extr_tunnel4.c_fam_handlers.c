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
struct xfrm_tunnel {int dummy; } ;

/* Variables and functions */
 unsigned short AF_INET ; 
 struct xfrm_tunnel* tunnel4_handlers ; 
 struct xfrm_tunnel* tunnel64_handlers ; 

__attribute__((used)) static inline struct xfrm_tunnel **fam_handlers(unsigned short family)
{
	return (family == AF_INET) ? &tunnel4_handlers : &tunnel64_handlers;
}