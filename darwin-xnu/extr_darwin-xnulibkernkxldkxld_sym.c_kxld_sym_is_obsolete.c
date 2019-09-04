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
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ is_obsolete; } ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */

boolean_t
kxld_sym_is_obsolete(const KXLDSym *sym)
{
    return (0 != sym->is_obsolete);
}