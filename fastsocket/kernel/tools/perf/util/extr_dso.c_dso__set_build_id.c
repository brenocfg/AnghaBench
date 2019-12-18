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
struct dso {int has_build_id; int /*<<< orphan*/  build_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

void dso__set_build_id(struct dso *dso, void *build_id)
{
	memcpy(dso->build_id, build_id, sizeof(dso->build_id));
	dso->has_build_id = 1;
}