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
 int MAXLINE ; 
 int bsize ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/ * cp ; 
 int /*<<< orphan*/ * file ; 
 int /*<<< orphan*/  fillbuf () ; 
 int /*<<< orphan*/ * limit ; 
 scalar_t__ lineno ; 
 int /*<<< orphan*/  main_init (int,char**) ; 
 int /*<<< orphan*/  nextline () ; 

void input_init(int argc, char *argv[]) {
	static int inited;

	if (inited)
		return;
	inited = 1;
	main_init(argc, argv);
	limit = cp = &buffer[MAXLINE+1];
	bsize = -1;
	lineno = 0;
	file = NULL;
	fillbuf();
	if (cp >= limit)
		cp = limit;
	nextline();
}