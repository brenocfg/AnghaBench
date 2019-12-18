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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/ * func_params ; 
 int /*<<< orphan*/  put_error () ; 
 int /*<<< orphan*/  stderr ; 
 char* yytext ; 

__attribute__((used)) static void
yaccError (const char *msg)
{
    func_params = NULL;
    put_error();		/* tell what line we're on, and what file */
    fprintf(stderr, "%s at token '%s'\n", msg, yytext);
}