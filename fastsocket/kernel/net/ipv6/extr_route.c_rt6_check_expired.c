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
struct rt6_info {int rt6i_flags; int /*<<< orphan*/  rt6i_expires; } ;

/* Variables and functions */
 int RTF_EXPIRES ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int rt6_check_expired(const struct rt6_info *rt)
{
	return (rt->rt6i_flags & RTF_EXPIRES &&
		time_after(jiffies, rt->rt6i_expires));
}