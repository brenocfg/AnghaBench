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
 size_t SIZE_T_MAX ; 
 size_t SOTCIX_AV ; 
 size_t SOTCIX_BE ; 
 size_t SOTCIX_BK ; 
 size_t SOTCIX_BK_SYS ; 
 size_t SOTCIX_CTL ; 
 size_t SOTCIX_OAM ; 
 size_t SOTCIX_RD ; 
 size_t SOTCIX_RV ; 
 size_t SOTCIX_VI ; 
 size_t SOTCIX_VO ; 
#define  SO_TC_AV 140 
#define  SO_TC_BE 139 
#define  SO_TC_BK 138 
#define  SO_TC_BK_SYS 137 
#define  SO_TC_CTL 136 
#define  SO_TC_OAM 135 
#define  SO_TC_RD 134 
#define  SO_TC_RV 133 
#define  SO_TC_VI 132 
#define  SO_TC_VO 131 
#define  _SO_TC_BK 130 
#define  _SO_TC_VI 129 
#define  _SO_TC_VO 128 

__attribute__((used)) static size_t
sotc_index(int sotc)
{
	switch (sotc) {
		case SO_TC_BK_SYS:
			return (SOTCIX_BK_SYS);
		case _SO_TC_BK:
		case SO_TC_BK:
			return (SOTCIX_BK);

		case SO_TC_BE:
			return (SOTCIX_BE);
		case SO_TC_RD:
			return (SOTCIX_RD);
		case SO_TC_OAM:
			return (SOTCIX_OAM);

		case SO_TC_AV:
			return (SOTCIX_AV);
		case SO_TC_RV:
			return (SOTCIX_RV);
		case _SO_TC_VI:
		case SO_TC_VI:
			return (SOTCIX_VI);

		case _SO_TC_VO:
		case SO_TC_VO:
			return (SOTCIX_VO);
		case SO_TC_CTL:
			return (SOTCIX_CTL);

		default:
			break;
	}
	/*
	 * Unknown traffic class value
	 */
	return (SIZE_T_MAX);
}