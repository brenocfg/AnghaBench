#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_5__ {int pal_bus_features_val; } ;
typedef  TYPE_1__ pal_bus_features_u_t ;

/* Variables and functions */
 char** bus_features ; 
 int /*<<< orphan*/  ia64_pal_bus_get_features (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*,char*,char*) ; 

__attribute__((used)) static int
bus_info(char *page)
{
	char *p = page;
	const char **v = bus_features;
	pal_bus_features_u_t av, st, ct;
	u64 avail, status, control;
	int i;
	s64 ret;

	if ((ret=ia64_pal_bus_get_features(&av, &st, &ct)) != 0) return 0;

	avail   = av.pal_bus_features_val;
	status  = st.pal_bus_features_val;
	control = ct.pal_bus_features_val;

	for(i=0; i < 64; i++, v++, avail >>=1, status >>=1, control >>=1) {
		if ( ! *v ) continue;
		p += sprintf(p, "%-48s : %s%s %s\n", *v,
				avail & 0x1 ? "" : "NotImpl",
				avail & 0x1 ? (status  & 0x1 ? "On" : "Off"): "",
				avail & 0x1 ? (control & 0x1 ? "Ctrl" : "NoCtrl"): "");
	}
	return p - page;
}