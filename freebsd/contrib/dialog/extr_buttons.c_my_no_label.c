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
struct TYPE_2__ {char const* no_label; } ;

/* Variables and functions */
 char const* _ (char*) ; 
 TYPE_1__ dialog_vars ; 

__attribute__((used)) static const char *
my_no_label(void)
{
    return (dialog_vars.no_label != NULL)
	? dialog_vars.no_label
	: _("No");
}