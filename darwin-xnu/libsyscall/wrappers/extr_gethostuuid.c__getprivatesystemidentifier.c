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
typedef  int /*<<< orphan*/  uuid_t ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int __gethostuuid (int /*<<< orphan*/ ,struct timespec const*,int) ; 

int
_getprivatesystemidentifier(uuid_t uuid, const struct timespec *timeout)
{
	return __gethostuuid(uuid, timeout, 1);
}