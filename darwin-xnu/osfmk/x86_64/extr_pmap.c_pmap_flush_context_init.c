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
struct TYPE_3__ {scalar_t__ pfc_invalid_global; scalar_t__ pfc_cpus; } ;
typedef  TYPE_1__ pmap_flush_context ;

/* Variables and functions */

void
pmap_flush_context_init(pmap_flush_context *pfc)
{
	pfc->pfc_cpus = 0;
	pfc->pfc_invalid_global = 0;
}