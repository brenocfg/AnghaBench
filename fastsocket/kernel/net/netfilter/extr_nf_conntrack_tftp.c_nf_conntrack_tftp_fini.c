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
 int /*<<< orphan*/  nf_conntrack_helper_unregister (int /*<<< orphan*/ *) ; 
 int ports_c ; 
 int /*<<< orphan*/ ** tftp ; 

__attribute__((used)) static void nf_conntrack_tftp_fini(void)
{
	int i, j;

	for (i = 0; i < ports_c; i++) {
		for (j = 0; j < 2; j++)
			nf_conntrack_helper_unregister(&tftp[i][j]);
	}
}