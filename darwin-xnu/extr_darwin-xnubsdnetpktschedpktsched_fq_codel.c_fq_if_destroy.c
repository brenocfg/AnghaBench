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
struct TYPE_5__ {int /*<<< orphan*/ * fqs_ifq; } ;
typedef  TYPE_1__ fq_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  fq_if_purge (TYPE_1__*) ; 
 int /*<<< orphan*/  fq_if_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
fq_if_destroy(fq_if_t *fqs)
{
	fq_if_purge(fqs);
	fqs->fqs_ifq = NULL;
	zfree(fq_if_zone, fqs);
}