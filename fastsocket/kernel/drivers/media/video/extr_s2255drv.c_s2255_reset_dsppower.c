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
struct s2255_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  s2255_vendor_req (struct s2255_dev*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s2255_reset_dsppower(struct s2255_dev *dev)
{
	s2255_vendor_req(dev, 0x40, 0x0b0b, 0x0b0b, NULL, 0, 1);
	msleep(10);
	s2255_vendor_req(dev, 0x50, 0x0000, 0x0000, NULL, 0, 1);
	return;
}