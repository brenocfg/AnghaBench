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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SGE_DBFIFO_STATUS ; 
 unsigned int G_HP_COUNT (int /*<<< orphan*/ ) ; 
 unsigned int G_LP_COUNT (int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device const*) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

unsigned int cxgb4_dbfifo_count(const struct net_device *dev, int lpfifo)
{
	struct adapter *adap = netdev2adap(dev);
	u32 v;

	v = t4_read_reg(adap, A_SGE_DBFIFO_STATUS);
	return lpfifo ? G_LP_COUNT(v) : G_HP_COUNT(v);
}