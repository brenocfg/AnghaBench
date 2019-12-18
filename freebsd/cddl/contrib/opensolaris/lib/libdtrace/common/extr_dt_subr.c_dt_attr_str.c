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
typedef  int /*<<< orphan*/  stability ;
struct TYPE_3__ {int dtat_name; int dtat_data; int dtat_class; } ;
typedef  TYPE_1__ dtrace_attribute_t ;
typedef  int /*<<< orphan*/  class ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const,char const,char const) ; 

char *
dt_attr_str(dtrace_attribute_t a, char *buf, size_t len)
{
	static const char stability[] = "ipoxuesS";
	static const char class[] = "uCpgIc";

	if (a.dtat_name < sizeof (stability) &&
	    a.dtat_data < sizeof (stability) && a.dtat_class < sizeof (class)) {
		(void) snprintf(buf, len, "[%c/%c/%c]", stability[a.dtat_name],
		    stability[a.dtat_data], class[a.dtat_class]);
	} else {
		(void) snprintf(buf, len, "[%u/%u/%u]",
		    a.dtat_name, a.dtat_data, a.dtat_class);
	}

	return (buf);
}