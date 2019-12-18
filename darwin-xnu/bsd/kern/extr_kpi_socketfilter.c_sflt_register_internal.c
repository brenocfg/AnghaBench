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
struct sflt_filter {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  sflt_register_common (struct sflt_filter const*,int,int,int,int) ; 

errno_t
sflt_register_internal(const struct sflt_filter *filter, int domain, int type,
    int	 protocol)
{
	return (sflt_register_common(filter, domain, type, protocol, true));
}