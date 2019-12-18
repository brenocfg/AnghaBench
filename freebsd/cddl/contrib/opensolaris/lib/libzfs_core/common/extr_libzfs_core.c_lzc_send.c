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
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;

/* Variables and functions */
 int lzc_send_resume (char const*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lzc_send(const char *snapname, const char *from, int fd,
    enum lzc_send_flags flags)
{
	return (lzc_send_resume(snapname, from, fd, flags, 0, 0));
}