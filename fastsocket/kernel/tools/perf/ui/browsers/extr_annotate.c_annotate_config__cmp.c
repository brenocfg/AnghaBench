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
struct annotate__config {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int annotate_config__cmp(const void *name, const void *cfgp)
{
	const struct annotate__config *cfg = cfgp;

	return strcmp(name, cfg->name);
}