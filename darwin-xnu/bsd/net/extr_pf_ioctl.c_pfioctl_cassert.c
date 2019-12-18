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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
#define  DIOCADDADDR 197 
#define  DIOCADDALTQ 196 
#define  DIOCADDRULE 195 
#define  DIOCADDSTATE 194 
#define  DIOCBEGINADDRS 193 
#define  DIOCCHANGEADDR 192 
#define  DIOCCHANGEALTQ 191 
#define  DIOCCHANGERULE 190 
#define  DIOCCLRIFFLAG 189 
#define  DIOCCLRRULECTRS 188 
#define  DIOCCLRSRCNODES 187 
#define  DIOCCLRSTATES 186 
#define  DIOCCLRSTATUS 185 
#define  DIOCDELETERULE 184 
#define  DIOCGETADDR 183 
#define  DIOCGETADDRS 182 
#define  DIOCGETALTQ 181 
#define  DIOCGETALTQS 180 
#define  DIOCGETLIMIT 179 
#define  DIOCGETQSTATS 178 
#define  DIOCGETRULE 177 
#define  DIOCGETRULES 176 
#define  DIOCGETRULESET 175 
#define  DIOCGETRULESETS 174 
#define  DIOCGETSRCNODES 173 
#define  DIOCGETSTARTERS 172 
#define  DIOCGETSTATE 171 
#define  DIOCGETSTATES 170 
#define  DIOCGETSTATUS 169 
#define  DIOCGETTIMEOUT 168 
#define  DIOCGIFSPEED 167 
#define  DIOCIGETIFACES 166 
#define  DIOCINSERTRULE 165 
#define  DIOCKILLSRCNODES 164 
#define  DIOCKILLSTATES 163 
#define  DIOCNATLOOK 162 
#define  DIOCOSFPADD 161 
#define  DIOCOSFPFLUSH 160 
#define  DIOCOSFPGET 159 
#define  DIOCRADDADDRS 158 
#define  DIOCRADDTABLES 157 
#define  DIOCRCLRADDRS 156 
#define  DIOCRCLRASTATS 155 
#define  DIOCRCLRTABLES 154 
#define  DIOCRCLRTSTATS 153 
#define  DIOCRDELADDRS 152 
#define  DIOCRDELTABLES 151 
#define  DIOCRGETADDRS 150 
#define  DIOCRGETASTATS 149 
#define  DIOCRGETTABLES 148 
#define  DIOCRGETTSTATS 147 
#define  DIOCRINADEFINE 146 
#define  DIOCRSETADDRS 145 
#define  DIOCRSETTFLAGS 144 
#define  DIOCRTSTADDRS 143 
#define  DIOCSETDEBUG 142 
#define  DIOCSETHOSTID 141 
#define  DIOCSETIFFLAG 140 
#define  DIOCSETLIMIT 139 
#define  DIOCSETSTATUSIF 138 
#define  DIOCSETTIMEOUT 137 
#define  DIOCSTART 136 
#define  DIOCSTARTALTQ 135 
#define  DIOCSTARTREF 134 
#define  DIOCSTOP 133 
#define  DIOCSTOPALTQ 132 
#define  DIOCSTOPREF 131 
#define  DIOCXBEGIN 130 
#define  DIOCXCOMMIT 129 
#define  DIOCXROLLBACK 128 

__attribute__((used)) static __attribute__((unused)) void
pfioctl_cassert(void)
{
	/*
	 * This is equivalent to _CASSERT() and the compiler wouldn't
	 * generate any instructions, thus for compile time only.
	 */
	switch ((u_long)0) {
	case 0:

	/* bsd/net/pfvar.h */
	case DIOCSTART:
	case DIOCSTOP:
	case DIOCADDRULE:
	case DIOCGETSTARTERS:
	case DIOCGETRULES:
	case DIOCGETRULE:
	case DIOCSTARTREF:
	case DIOCSTOPREF:
	case DIOCCLRSTATES:
	case DIOCGETSTATE:
	case DIOCSETSTATUSIF:
	case DIOCGETSTATUS:
	case DIOCCLRSTATUS:
	case DIOCNATLOOK:
	case DIOCSETDEBUG:
	case DIOCGETSTATES:
	case DIOCCHANGERULE:
	case DIOCINSERTRULE:
	case DIOCDELETERULE:
	case DIOCSETTIMEOUT:
	case DIOCGETTIMEOUT:
	case DIOCADDSTATE:
	case DIOCCLRRULECTRS:
	case DIOCGETLIMIT:
	case DIOCSETLIMIT:
	case DIOCKILLSTATES:
	case DIOCSTARTALTQ:
	case DIOCSTOPALTQ:
	case DIOCADDALTQ:
	case DIOCGETALTQS:
	case DIOCGETALTQ:
	case DIOCCHANGEALTQ:
	case DIOCGETQSTATS:
	case DIOCBEGINADDRS:
	case DIOCADDADDR:
	case DIOCGETADDRS:
	case DIOCGETADDR:
	case DIOCCHANGEADDR:
	case DIOCGETRULESETS:
	case DIOCGETRULESET:
	case DIOCRCLRTABLES:
	case DIOCRADDTABLES:
	case DIOCRDELTABLES:
	case DIOCRGETTABLES:
	case DIOCRGETTSTATS:
	case DIOCRCLRTSTATS:
	case DIOCRCLRADDRS:
	case DIOCRADDADDRS:
	case DIOCRDELADDRS:
	case DIOCRSETADDRS:
	case DIOCRGETADDRS:
	case DIOCRGETASTATS:
	case DIOCRCLRASTATS:
	case DIOCRTSTADDRS:
	case DIOCRSETTFLAGS:
	case DIOCRINADEFINE:
	case DIOCOSFPFLUSH:
	case DIOCOSFPADD:
	case DIOCOSFPGET:
	case DIOCXBEGIN:
	case DIOCXCOMMIT:
	case DIOCXROLLBACK:
	case DIOCGETSRCNODES:
	case DIOCCLRSRCNODES:
	case DIOCSETHOSTID:
	case DIOCIGETIFACES:
	case DIOCSETIFFLAG:
	case DIOCCLRIFFLAG:
	case DIOCKILLSRCNODES:
	case DIOCGIFSPEED:
		;
	}
}