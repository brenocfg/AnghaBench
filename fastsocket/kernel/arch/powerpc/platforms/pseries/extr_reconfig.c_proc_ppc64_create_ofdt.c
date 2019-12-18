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
struct proc_dir_entry {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdt_fops ; 
 struct proc_dir_entry* proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseries ; 

__attribute__((used)) static int proc_ppc64_create_ofdt(void)
{
	struct proc_dir_entry *ent;

	if (!machine_is(pseries))
		return 0;

	ent = proc_create("ppc64/ofdt", S_IWUSR, NULL, &ofdt_fops);
	if (ent)
		ent->size = 0;

	return 0;
}