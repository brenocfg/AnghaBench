#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * raw; int /*<<< orphan*/  name; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  addr; int /*<<< orphan*/ * raw; } ;
struct ins_operands {char* raw; TYPE_2__ source; TYPE_1__ target; } ;

/* Variables and functions */
 int /*<<< orphan*/  comment__symbol (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 char* strchr (char*,char) ; 
 void* strdup (char*) ; 

__attribute__((used)) static int mov__parse(struct ins_operands *ops)
{
	char *s = strchr(ops->raw, ','), *target, *comment, prev;

	if (s == NULL)
		return -1;

	*s = '\0';
	ops->source.raw = strdup(ops->raw);
	*s = ',';
	
	if (ops->source.raw == NULL)
		return -1;

	target = ++s;

	while (s[0] != '\0' && !isspace(s[0]))
		++s;
	prev = *s;
	*s = '\0';

	ops->target.raw = strdup(target);
	*s = prev;

	if (ops->target.raw == NULL)
		goto out_free_source;

	comment = strchr(s, '#');
	if (comment == NULL)
		return 0;

	while (comment[0] != '\0' && isspace(comment[0]))
		++comment;

	comment__symbol(ops->source.raw, comment, &ops->source.addr, &ops->source.name);
	comment__symbol(ops->target.raw, comment, &ops->target.addr, &ops->target.name);

	return 0;

out_free_source:
	free(ops->source.raw);
	ops->source.raw = NULL;
	return -1;
}