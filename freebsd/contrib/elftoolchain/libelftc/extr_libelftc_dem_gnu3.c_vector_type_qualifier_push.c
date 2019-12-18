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
struct vector_type_qualifier {size_t size; size_t capacity; int* q_container; } ;
typedef  enum type_qualifier { ____Placeholder_type_qualifier } type_qualifier ;

/* Variables and functions */
 size_t BUFFER_GROWFACTOR ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 

__attribute__((used)) static int
vector_type_qualifier_push(struct vector_type_qualifier *v,
    enum type_qualifier t)
{
	enum type_qualifier *tmp_ctn;
	size_t tmp_cap;
	size_t i;

	if (v == NULL)
		return (0);

	if (v->size == v->capacity) {
		tmp_cap = v->capacity * BUFFER_GROWFACTOR;
		if ((tmp_ctn = malloc(sizeof(enum type_qualifier) * tmp_cap))
		    == NULL)
			return (0);
		for (i = 0; i < v->size; ++i)
			tmp_ctn[i] = v->q_container[i];
		free(v->q_container);
		v->q_container = tmp_ctn;
		v->capacity = tmp_cap;
	}

	v->q_container[v->size] = t;
	++v->size;

	return (1);
}