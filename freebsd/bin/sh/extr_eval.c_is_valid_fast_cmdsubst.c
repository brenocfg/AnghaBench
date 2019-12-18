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
union node {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NCMD ; 

__attribute__((used)) static int
is_valid_fast_cmdsubst(union node *n)
{

	return (n->type == NCMD);
}