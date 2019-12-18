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
struct vector_type_qualifier {int capacity; int /*<<< orphan*/ * q_container; int /*<<< orphan*/  ext_name; scalar_t__ size; } ;
typedef  enum type_qualifier { ____Placeholder_type_qualifier } type_qualifier ;

/* Variables and functions */
 int VECTOR_DEF_CAPACITY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int vector_str_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vector_type_qualifier_init(struct vector_type_qualifier *v)
{

	if (v == NULL)
		return (0);

	v->size = 0;
	v->capacity = VECTOR_DEF_CAPACITY;

	if ((v->q_container = malloc(sizeof(enum type_qualifier) * v->capacity))
	    == NULL)
		return (0);

	assert(v->q_container != NULL);

	if (vector_str_init(&v->ext_name) == false) {
		free(v->q_container);
		return (0);
	}

	return (1);
}