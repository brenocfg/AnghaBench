#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ getword (char*) ; 
 TYPE_1__* lookup (char*,struct node**) ; 
 scalar_t__ next ; 
 int /*<<< orphan*/  tprint (struct node*) ; 

main() {
	struct node *root;
	char word[20];

	root = 0;
	next = 0;
	while (getword(word))
		lookup(word, &root)->count++;
	tprint(root);
	return 0;
}