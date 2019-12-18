#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ifr_flags; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  saved_errno ; 
 int /*<<< orphan*/  skfd ; 
 TYPE_1__ slave_flags ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_print (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_slave_flags(char *slave_ifname)
{
	int res = 0;

	strncpy(slave_flags.ifr_name, slave_ifname, IFNAMSIZ);
	res = ioctl(skfd, SIOCGIFFLAGS, &slave_flags);
	if (res < 0) {
		saved_errno = errno;
		v_print("Slave '%s': Error: SIOCGIFFLAGS failed: %s\n",
			slave_ifname, strerror(saved_errno));
	} else {
		v_print("Slave %s: flags %04X.\n",
			slave_ifname, slave_flags.ifr_flags);
	}

	return res;
}