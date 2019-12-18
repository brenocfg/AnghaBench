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
typedef  int boolean_t ;

/* Variables and functions */
 unsigned int KEVENT_FLAG_ERROR_EVENTS ; 

__attribute__((used)) static inline boolean_t
kevent_args_requesting_events(unsigned int flags, int nevents)
{
	return (!(flags & KEVENT_FLAG_ERROR_EVENTS) && nevents > 0);
}