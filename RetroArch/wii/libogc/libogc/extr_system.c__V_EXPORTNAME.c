#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  _V_DATE_ ; 
 int /*<<< orphan*/  _V_STRING ; 
 int /*<<< orphan*/  __sys_versionbuild ; 
 int /*<<< orphan*/  __sys_versiondate ; 

void _V_EXPORTNAME(void)
{ __sys_versionbuild = _V_STRING; __sys_versiondate = _V_DATE_; }