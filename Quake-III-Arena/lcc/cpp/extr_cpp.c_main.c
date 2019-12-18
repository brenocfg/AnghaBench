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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  Tokenrow ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curtime ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expandlex () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixlex () ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  genline () ; 
 int /*<<< orphan*/  iniths () ; 
 int /*<<< orphan*/  maketokenrow (int,int /*<<< orphan*/ *) ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setup (int,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	Tokenrow tr;
	time_t t;
	char ebuf[BUFSIZ];

	setbuf(stderr, ebuf);
	t = time(NULL);
	curtime = ctime(&t);
	maketokenrow(3, &tr);
	expandlex();
	setup(argc, argv);
	fixlex();
	iniths();
	genline();
	process(&tr);
	flushout();
	fflush(stderr);
	exit(nerrs > 0);
	return 0;
}