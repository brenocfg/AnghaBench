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

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  connect (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  log_addr ; 
 scalar_t__ log_fd ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __openlog()
{
	log_fd = socket(AF_UNIX, SOCK_DGRAM|SOCK_CLOEXEC, 0);
	if (log_fd >= 0) connect(log_fd, (void *)&log_addr, sizeof log_addr);
}