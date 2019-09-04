#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vector_upl_t ;
typedef  TYPE_2__* upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
struct TYPE_5__ {scalar_t__ vector_upl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pagelist; } ;

/* Variables and functions */

upl_page_info_t *
upl_get_internal_vectorupl_pagelist(upl_t upl)
{
	return ((vector_upl_t)(upl->vector_upl))->pagelist;
}