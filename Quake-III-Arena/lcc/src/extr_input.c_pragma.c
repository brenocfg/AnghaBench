#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID ; 
 char* cp ; 
 int /*<<< orphan*/  gettok () ; 
 int /*<<< orphan*/  src ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  token ; 
 TYPE_1__* tsym ; 
 int /*<<< orphan*/  use (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pragma(void) {
	if ((t = gettok()) == ID && strcmp(token, "ref") == 0)
		for (;;) {
			while (*cp == ' ' || *cp == '\t')
				cp++;
			if (*cp == '\n' || *cp == 0)
				break;
			if ((t = gettok()) == ID && tsym) {
				tsym->ref++;
				use(tsym, src);
			}	
		}
}