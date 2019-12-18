#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 TYPE_1__* parsefile ; 
 int /*<<< orphan*/  parselleft ; 
 char const* parsenextc ; 
 int /*<<< orphan*/  parsenleft ; 
 int plinno ; 
 int /*<<< orphan*/  pushfile () ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
setinputstring(const char *string, int push)
{
	INTOFF;
	if (push)
		pushfile();
	parsenextc = string;
	parselleft = parsenleft = strlen(string);
	parsefile->buf = NULL;
	plinno = 1;
	INTON;
}