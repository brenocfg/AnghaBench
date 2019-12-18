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
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  regs ; 
 char* s ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
YYERROR_DECL()
{
    UNUSED(regs); /* %parse-param regs is not actually used here */
    UNUSED(base); /* %parse-param base is not actually used here */
    fprintf(stderr, "%s\n", s);
}