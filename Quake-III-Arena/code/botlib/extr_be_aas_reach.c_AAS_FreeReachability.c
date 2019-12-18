#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ aas_lreachability_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* nextreachability ; 
 int /*<<< orphan*/  numlreachabilities ; 

void AAS_FreeReachability(aas_lreachability_t *lreach)
{
	Com_Memset(lreach, 0, sizeof(aas_lreachability_t));

	lreach->next = nextreachability;
	nextreachability = lreach;
	numlreachabilities--;
}