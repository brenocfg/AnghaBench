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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int RRexpect ; 
 int SRexpect ; 
 int /*<<< orphan*/  done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_code ; 
 int /*<<< orphan*/  finalize_closure () ; 
 int /*<<< orphan*/  getargs (int,char**) ; 
 int /*<<< orphan*/  graph () ; 
 int /*<<< orphan*/  lalr () ; 
 int /*<<< orphan*/  lr0 () ; 
 int /*<<< orphan*/  make_parser () ; 
 int /*<<< orphan*/  open_files () ; 
 int /*<<< orphan*/  output () ; 
 int /*<<< orphan*/  reader () ; 
 int /*<<< orphan*/  set_signals () ; 
 int /*<<< orphan*/  verbose () ; 

int
main(int argc, char *argv[])
{
    SRexpect = -1;
    RRexpect = -1;
    exit_code = EXIT_SUCCESS;

    set_signals();
    getargs(argc, argv);
    open_files();
    reader();
    lr0();
    lalr();
    make_parser();
    graph();
    finalize_closure();
    verbose();
    output();
    done(exit_code);
    /*NOTREACHED */
}