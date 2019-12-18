#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ ti; scalar_t__ rpl; scalar_t__ index; } ;
typedef  TYPE_1__ sel_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int access; } ;

/* Variables and functions */
 int ACC_PL_U ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDTSZ ; 
 scalar_t__ SEL_LDT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USER_PRIV ; 
 TYPE_3__* gdt_desc_p (scalar_t__) ; 
 TYPE_1__ selector_to_sel (scalar_t__) ; 

boolean_t
valid_user_stack_selector(uint16_t selector)
{
    sel_t	sel = selector_to_sel(selector);
    
    if (selector == 0)
    	return (FALSE);

    if (sel.ti == SEL_LDT) {
	if (sel.rpl == USER_PRIV)
	    return (TRUE);
    }
    else if (sel.index < GDTSZ && sel.rpl == USER_PRIV) {
	if ((gdt_desc_p(selector)->access & ACC_PL_U) == ACC_PL_U)
	    return (TRUE);
    }
		
    return (FALSE);
}