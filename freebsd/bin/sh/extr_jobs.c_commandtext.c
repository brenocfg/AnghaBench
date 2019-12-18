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
typedef  union node {int dummy; } node ;

/* Variables and functions */
 scalar_t__ MAXCMDTEXT ; 
 char* ckmalloc (scalar_t__) ; 
 char* cmdnextc ; 
 scalar_t__ cmdnleft ; 
 int /*<<< orphan*/  cmdtxt (union node*) ; 

char *
commandtext(union node *n)
{
	char *name;

	cmdnextc = name = ckmalloc(MAXCMDTEXT);
	cmdnleft = MAXCMDTEXT - 4;
	cmdtxt(n);
	*cmdnextc = '\0';
	return name;
}