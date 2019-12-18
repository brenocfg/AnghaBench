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
struct ratelimit_state {int dummy; } ;

/* Variables and functions */
 int __ratelimit (struct ratelimit_state*) ; 

__attribute__((used)) static inline int fastsocket_limit(void)
{
	//Declare the global variable inside this function to hide this varaible
	extern struct ratelimit_state fastsocket_ratelimit_state;
	
	return __ratelimit(&fastsocket_ratelimit_state);
}