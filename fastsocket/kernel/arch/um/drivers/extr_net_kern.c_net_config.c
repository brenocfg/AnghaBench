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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int eth_parse (char*,int*,char**,char**) ; 
 int /*<<< orphan*/  eth_setup_common (char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_config(char *str, char **error_out)
{
	int n, err;

	err = eth_parse(str, &n, &str, error_out);
	if (err)
		return err;

	/* This string is broken up and the pieces used by the underlying
	 * driver.  So, it is freed only if eth_setup_common fails.
	 */
	str = kstrdup(str, GFP_KERNEL);
	if (str == NULL) {
	        *error_out = "net_config failed to strdup string";
		return -ENOMEM;
	}
	err = !eth_setup_common(str, n);
	if (err)
		kfree(str);
	return err;
}