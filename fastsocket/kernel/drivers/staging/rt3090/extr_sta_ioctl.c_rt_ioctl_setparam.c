#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_10__ {char* name; int /*<<< orphan*/  (* set_proc ) (TYPE_1__*,char*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  ioctl_if; int /*<<< orphan*/  ioctl_if_type; } ;
struct TYPE_8__ {scalar_t__ OS_Cookie; } ;
typedef  char* PSTRING ;
typedef  TYPE_1__* PRTMP_ADAPTER ;
typedef  TYPE_2__* POS_COOKIE ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  INT_MAIN ; 
 int /*<<< orphan*/  MAIN_MBSSID ; 
 TYPE_5__* PRTMP_PRIVATE_SET_PROC ; 
 TYPE_1__* RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 TYPE_5__* RTMP_PRIVATE_SUPPORT_PROC ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_TRACE ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_IN_USE ; 
 char* rtstrchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

__attribute__((used)) static int
rt_ioctl_setparam(struct net_device *dev, struct iw_request_info *info,
			 void *w, char *extra)
{
	PRTMP_ADAPTER pAdapter;
	POS_COOKIE pObj;
	PSTRING this_char = extra;
	PSTRING value;
	int  Status=0;

	pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);
	if (pAdapter == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	pObj = (POS_COOKIE) pAdapter->OS_Cookie;
	{
		pObj->ioctl_if_type = INT_MAIN;
        pObj->ioctl_if = MAIN_MBSSID;
	}

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAdapter, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
			return -ENETDOWN;
	}

	if (!*this_char)
		return -EINVAL;

	if ((value = rtstrchr(this_char, '=')) != NULL)
	    *value++ = 0;

	if (!value && (strcmp(this_char, "SiteSurvey") != 0))
	    return -EINVAL;
	else
		goto SET_PROC;

	// reject setting nothing besides ANY ssid(ssidLen=0)
    if (!*value && (strcmp(this_char, "SSID") != 0))
        return -EINVAL;

SET_PROC:
	for (PRTMP_PRIVATE_SET_PROC = RTMP_PRIVATE_SUPPORT_PROC; PRTMP_PRIVATE_SET_PROC->name; PRTMP_PRIVATE_SET_PROC++)
	{
	    if (strcmp(this_char, PRTMP_PRIVATE_SET_PROC->name) == 0)
	    {
	        if(!PRTMP_PRIVATE_SET_PROC->set_proc(pAdapter, value))
	        {	//FALSE:Set private failed then return Invalid argument
			    Status = -EINVAL;
	        }
		    break;	//Exit for loop.
	    }
	}

	if(PRTMP_PRIVATE_SET_PROC->name == NULL)
	{  //Not found argument
	    Status = -EINVAL;
	    DBGPRINT(RT_DEBUG_TRACE, ("===>rt_ioctl_setparam:: (iwpriv) Not Support Set Command [%s=%s]\n", this_char, value));
	}

    return Status;
}