#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct module {int /*<<< orphan*/  module_core; int /*<<< orphan*/  core_size; scalar_t__ refptr; scalar_t__ percpu; int /*<<< orphan*/  args; int /*<<< orphan*/  module_init; int /*<<< orphan*/  num_kp; int /*<<< orphan*/  kp; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unlink_module ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ddebug_remove_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_free_key_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_kobject_remove (struct module*) ; 
 int /*<<< orphan*/  module_arch_cleanup (struct module*) ; 
 int /*<<< orphan*/  module_free (struct module*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unload_free (struct module*) ; 
 int /*<<< orphan*/  percpu_modfree (scalar_t__) ; 
 int /*<<< orphan*/  remove_notes_attrs (struct module*) ; 
 int /*<<< orphan*/  remove_sect_attrs (struct module*) ; 
 int /*<<< orphan*/  stop_machine (int /*<<< orphan*/ ,struct module*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_module_free (struct module*) ; 
 int /*<<< orphan*/  update_protections (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_module(struct module *mod)
{
	trace_module_free(mod);

	/* Delete from various lists */
	stop_machine(__unlink_module, mod, NULL);
	remove_notes_attrs(mod);
	remove_sect_attrs(mod);
	mod_kobject_remove(mod);

	/* Remove dynamic debug info */
	ddebug_remove_module(mod->name);

	/* Arch-specific cleanup. */
	module_arch_cleanup(mod);

	/* Module unload stuff */
	module_unload_free(mod);

	/* Free any allocated parameters. */
	destroy_params(mod->kp, mod->num_kp);

	/* This may be NULL, but that's OK */
	module_free(mod, mod->module_init);
	kfree(mod->args);
	if (mod->percpu)
		percpu_modfree(mod->percpu);
#if defined(CONFIG_MODULE_UNLOAD) && defined(CONFIG_SMP)
	if (mod->refptr)
		percpu_modfree(mod->refptr);
#endif
	/* Free lock-classes: */
	lockdep_free_key_range(mod->module_core, mod->core_size);

	/* Finally, free the core (containing the module structure) */
	module_free(mod, mod->module_core);

#ifdef CONFIG_MPU
	update_protections(current->mm);
#endif
}