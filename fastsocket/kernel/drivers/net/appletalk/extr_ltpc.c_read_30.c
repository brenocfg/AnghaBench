#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct TYPE_6__ {TYPE_1__ getflags; } ;
typedef  TYPE_2__ lt_command ;

/* Variables and functions */
 int /*<<< orphan*/  LT_GETFLAGS ; 
 int do_read (struct net_device*,TYPE_2__*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_30 ( struct net_device *dev)
{
	lt_command c;
	c.getflags.command = LT_GETFLAGS;
	return do_read(dev, &c, sizeof(c.getflags),&c,0);
}