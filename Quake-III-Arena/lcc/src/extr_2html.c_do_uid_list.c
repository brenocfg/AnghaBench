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
typedef  int /*<<< orphan*/  list_ty ;

/* Variables and functions */
 scalar_t__ Seq_get (int /*<<< orphan*/ ,int) ; 
 int Seq_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_uid (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void do_uid_list(list_ty x) {
	int i, count = Seq_length(x);

	if (count == 0)
		printf("<em>empty int list</em>\n");
	else {
		int i;
		printf("<em>int list</em>");
		for (i= 0; i < count; i++) {
			printf(" ");
			do_uid(*(int *)Seq_get(x, i));
		}
	}
}