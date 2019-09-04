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
typedef  int nl_item ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int CODESET ; 
 char* LCTRANS (char const*,int,int /*<<< orphan*/ ) ; 
#define  LC_MESSAGES 131 
#define  LC_MONETARY 130 
#define  LC_NUMERIC 129 
#define  LC_TIME 128 
 int MB_CUR_MAX ; 
 char* c_messages ; 
 char* c_numeric ; 
 char* c_time ; 

char *__nl_langinfo_l(nl_item item, locale_t loc)
{
	int cat = item >> 16;
	int idx = item & 65535;
	const char *str;

	if (item == CODESET) return MB_CUR_MAX==1 ? "ASCII" : "UTF-8";
	
	switch (cat) {
	case LC_NUMERIC:
		if (idx > 1) return "";
		str = c_numeric;
		break;
	case LC_TIME:
		if (idx > 0x31) return "";
		str = c_time;
		break;
	case LC_MONETARY:
		if (idx > 0) return "";
		str = "";
		break;
	case LC_MESSAGES:
		if (idx > 3) return "";
		str = c_messages;
		break;
	default:
		return "";
	}

	for (; idx; idx--, str++) for (; *str; str++);
	if (cat != LC_NUMERIC && *str) str = LCTRANS(str, cat, loc);
	return (char *)str;
}