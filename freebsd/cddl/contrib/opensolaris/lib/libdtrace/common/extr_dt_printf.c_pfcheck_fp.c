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
typedef  int /*<<< orphan*/  dt_pfargv_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int dt_node_is_float (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pfcheck_fp(dt_pfargv_t *pfv, dt_pfargd_t *pfd, dt_node_t *dnp)
{
	return (dt_node_is_float(dnp));
}