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
struct TYPE_3__ {struct TYPE_3__* t_tdesc; int /*<<< orphan*/  t_id; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdesc_name (TYPE_1__*) ; 

__attribute__((used)) static int
die_fwd_map(void *arg1, void *arg2)
{
	tdesc_t *fwd = arg1, *sou = arg2;

	debug(3, "tdp %u: mapped forward %s to sou %u\n", fwd->t_id,
	    tdesc_name(fwd), sou->t_id);
	fwd->t_tdesc = sou;

	return (0);
}