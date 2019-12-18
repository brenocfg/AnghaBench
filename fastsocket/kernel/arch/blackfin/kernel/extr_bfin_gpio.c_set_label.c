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
struct TYPE_2__ {scalar_t__* name; } ;

/* Variables and functions */
 int RESOURCE_LABEL_SIZE ; 
 TYPE_1__* str_ident ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 

__attribute__((used)) static void set_label(unsigned short ident, const char *label)
{
	if (label) {
		strncpy(str_ident[ident].name, label,
			 RESOURCE_LABEL_SIZE);
		str_ident[ident].name[RESOURCE_LABEL_SIZE - 1] = 0;
	}
}