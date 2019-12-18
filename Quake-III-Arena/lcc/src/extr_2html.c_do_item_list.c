#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rcc_item_ty ;
typedef  int /*<<< orphan*/  list_ty ;
struct TYPE_4__ {int uid; } ;

/* Variables and functions */
 TYPE_1__* Seq_get (int /*<<< orphan*/ ,int) ; 
 int Seq_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void do_item_list(list_ty x) {
	int count = Seq_length(x);

	if (count == 0)
		printf("<em>empty item list</em>\n");
	else {
		int i;
		printf("<em>item list</em>");
		printf("<ol>\n");
		for (i = 0; i < count; i++) {
			rcc_item_ty item = Seq_get(x, i);
			printf("<li value=%d>", item->uid);
			do_item(item);
			printf("</li>\n");
		}
		printf("</ol>\n");
	}
}