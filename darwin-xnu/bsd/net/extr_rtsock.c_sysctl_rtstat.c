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
struct sysctl_req {int dummy; } ;
struct rtstat {int dummy; } ;

/* Variables and functions */
 int SYSCTL_OUT (struct sysctl_req*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtstat ; 

__attribute__((used)) static int
sysctl_rtstat(struct sysctl_req *req)
{
	return (SYSCTL_OUT(req, &rtstat, sizeof (struct rtstat)));
}