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
struct scripting_ops {int dummy; } ;
struct scripting_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int script_spec_register (char*,struct scripting_ops*) ; 
 int /*<<< orphan*/  scripting_context ; 

__attribute__((used)) static void register_perl_scripting(struct scripting_ops *scripting_ops)
{
	int err;
	err = script_spec_register("Perl", scripting_ops);
	if (err)
		die("error registering Perl script extension");

	err = script_spec_register("pl", scripting_ops);
	if (err)
		die("error registering pl script extension");

	scripting_context = malloc(sizeof(struct scripting_context));
}