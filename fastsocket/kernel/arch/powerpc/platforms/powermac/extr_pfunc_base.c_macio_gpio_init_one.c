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
typedef  unsigned long u32 ;
struct macio_chip {struct device_node* of_node; scalar_t__ base; } ;
struct device_node {int /*<<< orphan*/  full_name; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMF_FLAGS_ON_INIT ; 
 int /*<<< orphan*/  macio_gpio_handlers ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 unsigned long* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_do_functions (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_register_driver (struct device_node*,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void macio_gpio_init_one(struct macio_chip *macio)
{
	struct device_node *gparent, *gp;

	/*
	 * Find the "gpio" parent node
	 */

	for (gparent = NULL;
	     (gparent = of_get_next_child(macio->of_node, gparent)) != NULL;)
		if (strcmp(gparent->name, "gpio") == 0)
			break;
	if (gparent == NULL)
		return;

	DBG("Installing GPIO functions for macio %s\n",
	    macio->of_node->full_name);

	/*
	 * Ok, got one, we dont need anything special to track them down, so
	 * we just create them all
	 */
	for (gp = NULL; (gp = of_get_next_child(gparent, gp)) != NULL;) {
		const u32 *reg = of_get_property(gp, "reg", NULL);
		unsigned long offset;
		if (reg == NULL)
			continue;
		offset = *reg;
		/* Deal with old style device-tree. We can safely hard code the
		 * offset for now too even if it's a bit gross ...
		 */
		if (offset < 0x50)
			offset += 0x50;
		offset += (unsigned long)macio->base;
		pmf_register_driver(gp, &macio_gpio_handlers, (void *)offset);
	}

	DBG("Calling initial GPIO functions for macio %s\n",
	    macio->of_node->full_name);

	/* And now we run all the init ones */
	for (gp = NULL; (gp = of_get_next_child(gparent, gp)) != NULL;)
		pmf_do_functions(gp, NULL, 0, PMF_FLAGS_ON_INIT, NULL);

	/* Note: We do not at this point implement the "at sleep" or "at wake"
	 * functions. I yet to find any for GPIOs anyway
	 */
}