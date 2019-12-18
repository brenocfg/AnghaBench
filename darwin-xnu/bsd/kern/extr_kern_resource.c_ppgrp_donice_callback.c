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
struct ppgrp_nice_args {int* errorp; int* foundp; int /*<<< orphan*/  prio; int /*<<< orphan*/  curp; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int PROC_RETURNED ; 
 int donice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppgrp_donice_callback(proc_t p, void * arg)
{
	int error;
	struct ppgrp_nice_args * pun = (struct ppgrp_nice_args *)arg;
	int n;

	error = donice(pun->curp, p, pun->prio);
	if (pun->errorp != NULL)
		*pun->errorp = error;
	if (pun->foundp!= NULL) {
		n = *pun->foundp;
		*pun->foundp = n+1;
	}

	return(PROC_RETURNED);
}