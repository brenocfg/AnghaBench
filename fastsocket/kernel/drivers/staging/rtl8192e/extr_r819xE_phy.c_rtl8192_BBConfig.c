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
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  rtl8192_BB_Config_ParaFile (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_InitBBRFRegDef (struct net_device*) ; 

RT_STATUS rtl8192_BBConfig(struct net_device* dev)
{
	RT_STATUS	rtStatus = RT_STATUS_SUCCESS;
	rtl8192_InitBBRFRegDef(dev);
	//config BB&RF. As hardCode based initialization has not been well
	//implemented, so use file first.FIXME:should implement it for hardcode?
	rtStatus = rtl8192_BB_Config_ParaFile(dev);
	return rtStatus;
}