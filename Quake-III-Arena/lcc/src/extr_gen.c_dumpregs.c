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
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/ * freemask ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void dumpregs(char *msg, char *a, char *b) {
	fprint(stderr, msg, a, b);
	fprint(stderr, "(free[0]=%x)\n", freemask[0]);
	fprint(stderr, "(free[1]=%x)\n", freemask[1]);
}