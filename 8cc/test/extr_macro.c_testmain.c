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
 int /*<<< orphan*/  cond_incl () ; 
 int /*<<< orphan*/  const_expr () ; 
 int /*<<< orphan*/  counter () ; 
 int /*<<< orphan*/  defined () ; 
 int /*<<< orphan*/  empty () ; 
 int /*<<< orphan*/  funclike () ; 
 int /*<<< orphan*/  gnuext () ; 
 int /*<<< orphan*/  ifdef () ; 
 int /*<<< orphan*/  include () ; 
 int /*<<< orphan*/  loop () ; 
 int /*<<< orphan*/  noarg () ; 
 int /*<<< orphan*/  null () ; 
 int /*<<< orphan*/  predefined () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  simple () ; 
 int /*<<< orphan*/  special () ; 
 int /*<<< orphan*/  undef () ; 

void testmain() {
    print("macros");
    special();
    include();
    predefined();
    simple();
    loop();
    undef();
    cond_incl();
    const_expr();
    defined();
    ifdef();
    funclike();
    empty();
    noarg();
    null();
    counter();
    gnuext();
}