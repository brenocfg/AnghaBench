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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int UINT ;

/* Variables and functions */
#define  TRAFFIC_TYPE_DOWNLOAD 129 
#define  TRAFFIC_TYPE_UPLOAD 128 
 int /*<<< orphan*/ * _UU (char*) ; 

wchar_t *GetTtcTypeStr(UINT type)
{
	switch (type)
	{
	case TRAFFIC_TYPE_DOWNLOAD:
		return _UU("TTC_TYPE_DOWNLOAD");

	case TRAFFIC_TYPE_UPLOAD:
		return _UU("TTC_TYPE_UPLOAD");

	default:
		return _UU("TTC_TYPE_FULL");
	}
}