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
 void* Seq_get (int /*<<< orphan*/ ,int) ; 
 int Seq_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void do_list(list_ty x, void do_one(void *), char *type, char *listhtml, char *separator) {
	int count = Seq_length(x);

	if (count == 0)
		printf("<em>empty %s list</em>\n", type);
	else {
		int i;
		printf("<em>%s list</em>", type);
		if (listhtml != NULL)
			printf("<%s>\n", listhtml);
		for (i = 0; i < count; i++) {
			if (listhtml != NULL)
				printf("<li>");
			printf(separator);
			do_one(Seq_get(x, i));
			if (listhtml != NULL)
				printf("</li>\n");
		}
		if (listhtml != NULL)
			printf("</%s>\n", listhtml);
	}
}