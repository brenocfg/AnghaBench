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
typedef  int /*<<< orphan*/  s_svis ;

/* Variables and functions */
#define  STV_DEFAULT 131 
#define  STV_HIDDEN 130 
#define  STV_INTERNAL 129 
#define  STV_PROTECTED 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
st_vis(unsigned int svis)
{
	static char s_svis[32];

	switch(svis) {
	case STV_DEFAULT: return "DEFAULT";
	case STV_INTERNAL: return "INTERNAL";
	case STV_HIDDEN: return "HIDDEN";
	case STV_PROTECTED: return "PROTECTED";
	default:
		snprintf(s_svis, sizeof(s_svis), "<unknown: %#x>", svis);
		return (s_svis);
	}
}