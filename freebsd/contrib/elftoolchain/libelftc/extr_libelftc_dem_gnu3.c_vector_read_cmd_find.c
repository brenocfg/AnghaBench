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
struct vector_read_cmd {struct read_cmd_item* r_container; scalar_t__ size; } ;
struct read_cmd_item {int cmd; } ;
typedef  enum read_cmd { ____Placeholder_read_cmd } read_cmd ;

/* Variables and functions */
 int READ_FAIL ; 

__attribute__((used)) static struct read_cmd_item *
vector_read_cmd_find(struct vector_read_cmd *v, enum read_cmd dst)
{
	int i;

	if (v == NULL || dst == READ_FAIL)
		return (NULL);

	for (i = (int) v->size - 1; i >= 0; i--)
		if (v->r_container[i].cmd == dst)
			return (&v->r_container[i]);

	return (NULL);
}