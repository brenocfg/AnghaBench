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
struct transport {int /*<<< orphan*/  (* setup ) (char*,char**,void*) ;int /*<<< orphan*/  setup_size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (char*,char**,void*) ; 

__attribute__((used)) static int check_transport(struct transport *transport, char *eth, int n,
			   void **init_out, char **mac_out)
{
	int len;

	len = strlen(transport->name);
	if (strncmp(eth, transport->name, len))
		return 0;

	eth += len;
	if (*eth == ',')
		eth++;
	else if (*eth != '\0')
		return 0;

	*init_out = kmalloc(transport->setup_size, GFP_KERNEL);
	if (*init_out == NULL)
		return 1;

	if (!transport->setup(eth, mac_out, *init_out)) {
		kfree(*init_out);
		*init_out = NULL;
	}
	return 1;
}