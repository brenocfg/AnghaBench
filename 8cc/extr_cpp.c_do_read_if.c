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
 int /*<<< orphan*/  cond_incl_stack ; 
 int /*<<< orphan*/  make_cond_incl (int) ; 
 int /*<<< orphan*/  skip_cond_incl () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_read_if(bool istrue) {
    vec_push(cond_incl_stack, make_cond_incl(istrue));
    if (!istrue)
        skip_cond_incl();
}