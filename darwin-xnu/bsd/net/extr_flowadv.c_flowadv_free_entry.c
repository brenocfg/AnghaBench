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
struct flowadv_fcentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fadv_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct flowadv_fcentry*) ; 

void
flowadv_free_entry(struct flowadv_fcentry *fce)
{
	zfree(fadv_zone, fce);
}