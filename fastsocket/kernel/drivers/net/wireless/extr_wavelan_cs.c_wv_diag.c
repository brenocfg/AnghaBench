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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP0_DIAGNOSE ; 
 int /*<<< orphan*/  SR0_DIAGNOSE_PASSED ; 
 int wv_82593_cmd (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
wv_diag(struct net_device *	dev)
{
  return(wv_82593_cmd(dev, "wv_diag(): diagnose",
		      OP0_DIAGNOSE, SR0_DIAGNOSE_PASSED));
}