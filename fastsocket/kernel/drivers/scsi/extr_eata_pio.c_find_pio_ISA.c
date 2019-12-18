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
struct get_conf {int dummy; } ;

/* Variables and functions */
 scalar_t__* ISAbases ; 
 int MAXISA ; 
 int /*<<< orphan*/  get_pio_conf_PIO (scalar_t__,struct get_conf*) ; 
 int /*<<< orphan*/  register_pio_HBA (scalar_t__,struct get_conf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void find_pio_ISA(struct get_conf *buf)
{
	int i;

	for (i = 0; i < MAXISA; i++) {
		if (!ISAbases[i])
			continue;
		if (!get_pio_conf_PIO(ISAbases[i], buf))
			continue;
		if (!register_pio_HBA(ISAbases[i], buf, NULL))
			release_region(ISAbases[i], 9);
		else
			ISAbases[i] = 0;
	}
	return;
}