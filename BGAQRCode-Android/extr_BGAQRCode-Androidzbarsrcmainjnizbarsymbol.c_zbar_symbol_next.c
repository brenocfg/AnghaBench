#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__ const* next; } ;
typedef  TYPE_1__ zbar_symbol_t ;

/* Variables and functions */

const zbar_symbol_t *zbar_symbol_next (const zbar_symbol_t *sym)
{
    return((sym) ? sym->next : NULL);
}