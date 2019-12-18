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
struct TYPE_3__ {uintptr_t sl_len; scalar_t__ sl_base; } ;
typedef  TYPE_1__ mcl_slab_t ;
typedef  int boolean_t ;

/* Variables and functions */

__attribute__((used)) static boolean_t
slab_inrange(mcl_slab_t *sp, void *buf)
{
	return ((uintptr_t)buf >= (uintptr_t)sp->sl_base &&
	    (uintptr_t)buf < ((uintptr_t)sp->sl_base + sp->sl_len));
}