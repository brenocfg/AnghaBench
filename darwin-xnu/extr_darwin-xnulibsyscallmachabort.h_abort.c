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
 int /*<<< orphan*/  __SIGABRT ; 
 int /*<<< orphan*/  __exit (int) ; 
 int /*<<< orphan*/  __getpid () ; 
 int /*<<< orphan*/  __kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __attribute__((noreturn))
abort(void) {
	(void)__kill(__getpid(), __SIGABRT, 0);
	__exit(1);
}