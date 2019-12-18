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
struct tdef {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct tdef*,int /*<<< orphan*/ ) ; 
 struct tdef* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  tdefs ; 

__attribute__((used)) static void
save_typdef(char *name)
{
	struct tdef *t;

	t = calloc(1, sizeof(struct tdef));
	if (t == NULL)
		err(1, NULL);

	t->name = name;
	SLIST_INSERT_HEAD(&tdefs, t, link);
}