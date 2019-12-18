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
 int /*<<< orphan*/  error (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void assert_string2(int line, char *s, char *t) {
    if (strcmp(s, t))
        error("%d: Expected \"%s\" but got \"%s\"", line, s, t);
}