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
 int /*<<< orphan*/ * in ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  putd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ *,int) ; 

main() {
	int i;

	sort(in, (sizeof in)/(sizeof in[0]));
	for (i = 0; i < (sizeof in)/(sizeof in[0]); i++) {
		putd(in[i]);
		putchar('\n');
	}
	return 0;
}