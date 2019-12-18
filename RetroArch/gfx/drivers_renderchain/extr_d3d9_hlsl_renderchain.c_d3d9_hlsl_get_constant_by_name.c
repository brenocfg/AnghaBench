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
typedef  int /*<<< orphan*/  lbl ;
typedef  int /*<<< orphan*/  LPD3DXCONSTANTTABLE ;

/* Variables and functions */
 void* d3d9x_constant_table_get_constant_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void *d3d9_hlsl_get_constant_by_name(void *data, const char *name)
{
   LPD3DXCONSTANTTABLE prog = (LPD3DXCONSTANTTABLE)data;
   char lbl[64];
   lbl[0] = '\0';
   snprintf(lbl, sizeof(lbl), "$%s", name);
   return d3d9x_constant_table_get_constant_by_name(prog, NULL, lbl);
}