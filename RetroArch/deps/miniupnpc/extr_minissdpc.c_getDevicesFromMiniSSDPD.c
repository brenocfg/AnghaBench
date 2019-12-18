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
struct UPNPDev {int dummy; } ;

/* Variables and functions */
 int connectToMiniSSDPD (char const*) ; 
 int /*<<< orphan*/  disconnectFromMiniSSDPD (int) ; 
 struct UPNPDev* receiveDevicesFromMiniSSDPD (int,int*) ; 
 int requestDevicesFromMiniSSDPD (int,char const*) ; 

struct UPNPDev *
getDevicesFromMiniSSDPD(const char * devtype, const char * socketpath, int * error)
{
	struct UPNPDev * devlist = NULL;
	int s;
	int res;

	s = connectToMiniSSDPD(socketpath);
	if (s < 0) {
		if (error)
			*error = s;
		return NULL;
	}
	res = requestDevicesFromMiniSSDPD(s, devtype);
	if (res < 0) {
		if (error)
			*error = res;
	} else {
		devlist = receiveDevicesFromMiniSSDPD(s, error);
	}
	disconnectFromMiniSSDPD(s);
	return devlist;
}