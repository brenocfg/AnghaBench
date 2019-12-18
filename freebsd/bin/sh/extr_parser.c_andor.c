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
typedef  union node {int dummy; } node ;

/* Variables and functions */
 int NAND ; 
 int NOR ; 
 int TAND ; 
 int TOR ; 
 union node* makebinary (int,union node*,union node*) ; 
 union node* pipeline () ; 
 int readtoken () ; 
 int /*<<< orphan*/  tokpushback ; 

__attribute__((used)) static union node *
andor(void)
{
	union node *n;
	int t;

	n = pipeline();
	for (;;) {
		if ((t = readtoken()) == TAND) {
			t = NAND;
		} else if (t == TOR) {
			t = NOR;
		} else {
			tokpushback++;
			return n;
		}
		n = makebinary(t, n, pipeline());
	}
}