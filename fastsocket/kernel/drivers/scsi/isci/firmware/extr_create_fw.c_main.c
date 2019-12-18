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
struct isci_orom {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct isci_orom*) ; 
 struct isci_orom* malloc (int) ; 
 int /*<<< orphan*/  memset (struct isci_orom*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_binary_values (struct isci_orom*) ; 
 int write_blob (struct isci_orom*) ; 

int main(void)
{
	int err;
	struct isci_orom *isci_orom;

	isci_orom = malloc(sizeof(struct isci_orom));
	memset(isci_orom, 0, sizeof(struct isci_orom));

	set_binary_values(isci_orom);

	err = write_blob(isci_orom);
	if (err < 0) {
		free(isci_orom);
		return err;
	}

	free(isci_orom);
	return 0;
}