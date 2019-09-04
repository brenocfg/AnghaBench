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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_NULL ; 
 int /*<<< orphan*/  current_proc () ; 
 int socreate_internal (int,struct socket**,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
socreate(int dom, struct socket **aso, int type, int proto)
{
	return (socreate_internal(dom, aso, type, proto, current_proc(), 0,
	    PROC_NULL));
}