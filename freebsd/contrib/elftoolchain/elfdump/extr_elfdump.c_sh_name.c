#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct elfdump {TYPE_1__* sl; int /*<<< orphan*/  shnum; } ;
typedef  int /*<<< orphan*/  num ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
#define  SHN_ABS 130 
#define  SHN_COMMON 129 
#define  SHN_UNDEF 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
sh_name(struct elfdump *ed, int ndx)
{
	static char num[10];

	switch (ndx) {
	case SHN_UNDEF: return "UNDEF";
	case SHN_ABS: return "ABS";
	case SHN_COMMON: return "COMMON";
	default:
		if ((uint64_t)ndx < ed->shnum)
			return (ed->sl[ndx].name);
		else {
			snprintf(num, sizeof(num), "%d", ndx);
			return (num);
		}
	}
}