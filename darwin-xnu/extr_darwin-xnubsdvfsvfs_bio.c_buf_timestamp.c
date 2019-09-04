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
struct timeval {int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  microuptime (struct timeval*) ; 

__attribute__((used)) static __inline__ int
buf_timestamp(void)
{
	struct	timeval		t;
	microuptime(&t);
	return (t.tv_sec);
}