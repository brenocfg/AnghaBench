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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,int) ; 
 int gettok () ; 
 int /*<<< orphan*/  printtoken () ; 
 int /*<<< orphan*/  stderr ; 
 int t ; 

void expect(int tok) {
	if (t == tok)
		t = gettok();
	else {
		error("syntax error; found");
		printtoken();
		fprint(stderr, " expecting `%k'\n", tok);
	}
}