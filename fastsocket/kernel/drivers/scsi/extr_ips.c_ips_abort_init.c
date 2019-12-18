#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ active; } ;
typedef  TYPE_1__ ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/  ips_free (TYPE_1__*) ; 
 int /*<<< orphan*/ ** ips_ha ; 
 int /*<<< orphan*/ ** ips_sh ; 

__attribute__((used)) static int
ips_abort_init(ips_ha_t * ha, int index)
{
	ha->active = 0;
	ips_free(ha);
	ips_ha[index] = NULL;
	ips_sh[index] = NULL;
	return -1;
}