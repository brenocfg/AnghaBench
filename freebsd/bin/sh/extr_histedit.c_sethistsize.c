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
typedef  int /*<<< orphan*/  HistEvent ;

/* Variables and functions */
 int /*<<< orphan*/  H_SETSIZE ; 
 int /*<<< orphan*/  H_SETUNIQUE ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/ * hist ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_number (char const*) ; 

void
sethistsize(const char *hs)
{
	int histsize;
	HistEvent he;

	if (hist != NULL) {
		if (hs == NULL || !is_number(hs))
			histsize = 100;
		else
			histsize = atoi(hs);
		history(hist, &he, H_SETSIZE, histsize);
		history(hist, &he, H_SETUNIQUE, 1);
	}
}