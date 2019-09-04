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
typedef  int /*<<< orphan*/  u_long ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int mdevioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct proc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdevbioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p) {
	return (mdevioctl(dev, cmd, data, flag, p, 0));
}