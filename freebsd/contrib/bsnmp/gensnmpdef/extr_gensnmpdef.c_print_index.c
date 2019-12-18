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
typedef  int /*<<< orphan*/  SmiNode ;
typedef  int /*<<< orphan*/  SmiElement ;

/* Variables and functions */
 int /*<<< orphan*/  print_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  smiGetElementNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smiGetFirstElement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smiGetNextElement (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_index(SmiNode *row)
{
	SmiElement *e;

	e = smiGetFirstElement(row);
	while (e != NULL) {
		printf(" ");
		print_type(smiGetElementNode(e));
		e = smiGetNextElement(e);
	}
}