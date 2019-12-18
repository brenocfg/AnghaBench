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
struct rfkill {int dummy; } ;
struct device {int dummy; } ;
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  eeepc_rfkill_ops ; 
 int get_acpi (int) ; 
 struct rfkill* rfkill_alloc (char const*,struct device*,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_init_sw_state (struct rfkill*,int) ; 
 int rfkill_register (struct rfkill*) ; 

__attribute__((used)) static int eeepc_new_rfkill(struct rfkill **rfkill,
			    const char *name, struct device *dev,
			    enum rfkill_type type, int cm)
{
	int result;

	result = get_acpi(cm);
	if (result < 0)
		return result;

	*rfkill = rfkill_alloc(name, dev, type,
			       &eeepc_rfkill_ops, (void *)(unsigned long)cm);

	if (!*rfkill)
		return -EINVAL;

	rfkill_init_sw_state(*rfkill, get_acpi(cm) != 1);
	result = rfkill_register(*rfkill);
	if (result) {
		rfkill_destroy(*rfkill);
		*rfkill = NULL;
		return result;
	}
	return 0;
}