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
struct ins {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct ins* bsearch (char const*,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ins__cmp ; 
 int /*<<< orphan*/  instructions ; 

__attribute__((used)) static struct ins *ins__find(const char *name)
{
	const int nmemb = ARRAY_SIZE(instructions);

	return bsearch(name, instructions, nmemb, sizeof(struct ins), ins__cmp);
}