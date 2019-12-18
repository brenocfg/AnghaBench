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
typedef  int /*<<< orphan*/  network_mysqld_keypart ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

void network_mysqld_keypart_free(network_mysqld_keypart *keypart) {
	if (!keypart) return;

	g_free(keypart);
}