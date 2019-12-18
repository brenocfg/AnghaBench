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
struct vector_read_cmd {size_t size; TYPE_1__* r_container; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_FAIL ; 

__attribute__((used)) static int
vector_read_cmd_pop(struct vector_read_cmd *v)
{

	if (v == NULL || v->size == 0)
		return (0);

	--v->size;
	v->r_container[v->size].cmd = READ_FAIL;
	v->r_container[v->size].data = NULL;

	return (1);
}