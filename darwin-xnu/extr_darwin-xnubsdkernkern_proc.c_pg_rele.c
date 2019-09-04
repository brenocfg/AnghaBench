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
struct pgrp {int dummy; } ;

/* Variables and functions */
 struct pgrp* PGRP_NULL ; 
 int /*<<< orphan*/  pg_rele_dropref (struct pgrp*) ; 

void
pg_rele(struct pgrp * pgrp)
{
	if(pgrp == PGRP_NULL)
		return;
	pg_rele_dropref(pgrp);
}