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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  addr; int /*<<< orphan*/ * raw; } ;
struct ins_operands {char* raw; TYPE_1__ target; } ;

/* Variables and functions */
 int /*<<< orphan*/  comment__symbol (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static int dec__parse(struct ins_operands *ops)
{
	char *target, *comment, *s, prev;

	target = s = ops->raw;

	while (s[0] != '\0' && !isspace(s[0]))
		++s;
	prev = *s;
	*s = '\0';

	ops->target.raw = strdup(target);
	*s = prev;

	if (ops->target.raw == NULL)
		return -1;

	comment = strchr(s, '#');
	if (comment == NULL)
		return 0;

	while (comment[0] != '\0' && isspace(comment[0]))
		++comment;

	comment__symbol(ops->target.raw, comment, &ops->target.addr, &ops->target.name);

	return 0;
}