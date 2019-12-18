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

/* Variables and functions */
 unsigned int VTXIOCCLRCACHE ; 
#define  VTXIOCCLRCACHE_OLD 139 
 unsigned int VTXIOCCLRFOUND ; 
#define  VTXIOCCLRFOUND_OLD 138 
 unsigned int VTXIOCCLRPAGE ; 
#define  VTXIOCCLRPAGE_OLD 137 
 unsigned int VTXIOCGETINFO ; 
#define  VTXIOCGETINFO_OLD 136 
 unsigned int VTXIOCGETPAGE ; 
#define  VTXIOCGETPAGE_OLD 135 
 unsigned int VTXIOCGETSTAT ; 
#define  VTXIOCGETSTAT_OLD 134 
 unsigned int VTXIOCPAGEREQ ; 
#define  VTXIOCPAGEREQ_OLD 133 
 unsigned int VTXIOCPUTPAGE ; 
#define  VTXIOCPUTPAGE_OLD 132 
 unsigned int VTXIOCPUTSTAT ; 
#define  VTXIOCPUTSTAT_OLD 131 
 unsigned int VTXIOCSETDISP ; 
#define  VTXIOCSETDISP_OLD 130 
 unsigned int VTXIOCSETVIRT ; 
#define  VTXIOCSETVIRT_OLD 129 
 unsigned int VTXIOCSTOPDAU ; 
#define  VTXIOCSTOPDAU_OLD 128 

__attribute__((used)) static inline unsigned int vtx_fix_command(unsigned int cmd)
{
	switch (cmd) {
	case VTXIOCGETINFO_OLD:
		cmd = VTXIOCGETINFO;
		break;
	case VTXIOCCLRPAGE_OLD:
		cmd = VTXIOCCLRPAGE;
		break;
	case VTXIOCCLRFOUND_OLD:
		cmd = VTXIOCCLRFOUND;
		break;
	case VTXIOCPAGEREQ_OLD:
		cmd = VTXIOCPAGEREQ;
		break;
	case VTXIOCGETSTAT_OLD:
		cmd = VTXIOCGETSTAT;
		break;
	case VTXIOCGETPAGE_OLD:
		cmd = VTXIOCGETPAGE;
		break;
	case VTXIOCSTOPDAU_OLD:
		cmd = VTXIOCSTOPDAU;
		break;
	case VTXIOCPUTPAGE_OLD:
		cmd = VTXIOCPUTPAGE;
		break;
	case VTXIOCSETDISP_OLD:
		cmd = VTXIOCSETDISP;
		break;
	case VTXIOCPUTSTAT_OLD:
		cmd = VTXIOCPUTSTAT;
		break;
	case VTXIOCCLRCACHE_OLD:
		cmd = VTXIOCCLRCACHE;
		break;
	case VTXIOCSETVIRT_OLD:
		cmd = VTXIOCSETVIRT;
		break;
	}
	return cmd;
}