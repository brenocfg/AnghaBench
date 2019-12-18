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
struct dbinfo {char* id; } ;
struct conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_change (char*,struct conf*,char*,int) ; 
 int /*<<< orphan*/  state ; 
 int state_iterate (int /*<<< orphan*/ ,struct conf*,struct dbinfo*,unsigned int) ; 

__attribute__((used)) static void
rules_restore(void)
{
	struct conf c;
	struct dbinfo dbi;
	unsigned int f;

	for (f = 1; state_iterate(state, &c, &dbi, f) == 1; f = 0) {
		if (dbi.id[0] == '\0')
			continue;
		(void)run_change("add", &c, dbi.id, sizeof(dbi.id));
	}
}