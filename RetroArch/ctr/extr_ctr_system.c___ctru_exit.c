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
 int /*<<< orphan*/  __appExit () ; 
 int /*<<< orphan*/  __libc_fini_array () ; 
 int /*<<< orphan*/  __libctru_exit (int) ; 

void __attribute__((noreturn)) __ctru_exit(int rc)
{
   __libc_fini_array();
   __appExit();
   __libctru_exit(rc);
}