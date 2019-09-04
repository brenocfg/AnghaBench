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
struct proc {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_IS_INTCOPROC (struct ifnet*) ; 
#define  SIOCGECNMODE 176 
#define  SIOCGIFAFLAG_IN6 175 
#define  SIOCGIFAGENTIDS32 174 
#define  SIOCGIFAGENTIDS64 173 
#define  SIOCGIFALIFETIME_IN6 172 
#define  SIOCGIFBOND 171 
#define  SIOCGIFBRDADDR 170 
#define  SIOCGIFCAP 169 
#define  SIOCGIFCONF32 168 
#define  SIOCGIFCONF64 167 
#define  SIOCGIFDELEGATE 166 
#define  SIOCGIFDESC 165 
#define  SIOCGIFDEVMTU 164 
#define  SIOCGIFEFLAGS 163 
#define  SIOCGIFEXPENSIVE 162 
#define  SIOCGIFFLAGS 161 
#define  SIOCGIFFUNCTIONALTYPE 160 
#define  SIOCGIFGENERIC 159 
#define  SIOCGIFGETRTREFCNT 158 
#define  SIOCGIFINFO_IN6 157 
#define  SIOCGIFINTERFACESTATE 156 
#define  SIOCGIFLINKPARAMS 155 
#define  SIOCGIFLINKQUALITYMETRIC 154 
#define  SIOCGIFLOG 153 
#define  SIOCGIFLOWINTERNET 152 
#define  SIOCGIFMAC 151 
#define  SIOCGIFMEDIA32 150 
#define  SIOCGIFMEDIA64 149 
#define  SIOCGIFMETRIC 148 
#define  SIOCGIFMTU 147 
#define  SIOCGIFNETMASK_IN6 146 
#define  SIOCGIFNETSIGNATURE 145 
#define  SIOCGIFOPPORTUNISTIC 144 
#define  SIOCGIFPDSTADDR 143 
#define  SIOCGIFPHYS 142 
#define  SIOCGIFPROBECONNECTIVITY 141 
#define  SIOCGIFPROTOLIST32 140 
#define  SIOCGIFPROTOLIST64 139 
#define  SIOCGIFPSRCADDR 138 
#define  SIOCGIFQUEUESTATS 137 
#define  SIOCGIFSTATUS 136 
#define  SIOCGIFTHROTTLE 135 
#define  SIOCGIFTIMESTAMPENABLED 134 
#define  SIOCGIFTYPE 133 
#define  SIOCGIFVLAN 132 
#define  SIOCGIFWAKEFLAGS 131 
#define  SIOCGNBRINFO_IN6 130 
#define  SIOCGQOSMARKINGENABLED 129 
#define  SIOCGQOSMARKINGMODE 128 
 scalar_t__ TRUE ; 
 struct ifnet* ifunit (char const*) ; 
 scalar_t__ intcoproc_unrestricted ; 
 scalar_t__ proc_pid (struct proc*) ; 

__attribute__((used)) static bool
ifioctl_restrict_intcoproc(unsigned long cmd, const char *ifname,
    struct ifnet *ifp, struct proc *p)
{

	if (intcoproc_unrestricted == TRUE) {
		return (false);
	}
	if (proc_pid(p) == 0) {
		return (false);
	}
	if (ifname) {
		ifp = ifunit(ifname);
	}
	if (ifp == NULL) {
		return (false);
	}
	if (!IFNET_IS_INTCOPROC(ifp)) {
		return (false);
	}
	switch (cmd) {
	case SIOCGIFBRDADDR:
	case SIOCGIFCONF32:
	case SIOCGIFCONF64:
	case SIOCGIFFLAGS:
	case SIOCGIFEFLAGS:
	case SIOCGIFCAP:
	case SIOCGIFMAC:
	case SIOCGIFMETRIC:
	case SIOCGIFMTU:
	case SIOCGIFPHYS:
	case SIOCGIFTYPE:
	case SIOCGIFFUNCTIONALTYPE:
	case SIOCGIFPSRCADDR:
	case SIOCGIFPDSTADDR:
	case SIOCGIFGENERIC:
	case SIOCGIFDEVMTU:
	case SIOCGIFVLAN:
	case SIOCGIFBOND:
	case SIOCGIFWAKEFLAGS:
	case SIOCGIFGETRTREFCNT:
	case SIOCGIFOPPORTUNISTIC:
	case SIOCGIFLINKQUALITYMETRIC:
	case SIOCGIFLOG:
	case SIOCGIFDELEGATE:
	case SIOCGIFEXPENSIVE:
	case SIOCGIFINTERFACESTATE:
	case SIOCGIFPROBECONNECTIVITY:
	case SIOCGIFTIMESTAMPENABLED:
	case SIOCGECNMODE:
	case SIOCGQOSMARKINGMODE:
	case SIOCGQOSMARKINGENABLED:
	case SIOCGIFLOWINTERNET:
	case SIOCGIFSTATUS:
	case SIOCGIFMEDIA32:
	case SIOCGIFMEDIA64:
	case SIOCGIFDESC:
	case SIOCGIFLINKPARAMS:
	case SIOCGIFQUEUESTATS:
	case SIOCGIFTHROTTLE:
	case SIOCGIFAGENTIDS32:
	case SIOCGIFAGENTIDS64:
	case SIOCGIFNETSIGNATURE:
	case SIOCGIFINFO_IN6:
	case SIOCGIFAFLAG_IN6:
	case SIOCGNBRINFO_IN6:
	case SIOCGIFALIFETIME_IN6:
	case SIOCGIFNETMASK_IN6:
	case SIOCGIFPROTOLIST32:
	case SIOCGIFPROTOLIST64:
		return (false);
	default:
#if (DEBUG || DEVELOPMENT)
		printf("%s: cmd 0x%lx not allowed (pid %u)\n",
		    __func__, cmd, proc_pid(p));
#endif
		return (true);
	}
	return (false);
}