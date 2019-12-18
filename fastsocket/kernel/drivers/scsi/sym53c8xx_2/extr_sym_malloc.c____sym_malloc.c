#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_pool_p ;
typedef  TYPE_2__* m_link_p ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
struct TYPE_4__ {TYPE_2__* h; } ;

/* Variables and functions */
 scalar_t__ M_GET_MEM_CLUSTER () ; 
 int SYM_MEM_CLUSTER_SIZE ; 
 int SYM_MEM_SHIFT ; 
 int /*<<< orphan*/  printf (char*,int,void*) ; 

__attribute__((used)) static void *___sym_malloc(m_pool_p mp, int size)
{
	int i = 0;
	int s = (1 << SYM_MEM_SHIFT);
	int j;
	void *a;
	m_link_p h = mp->h;

	if (size > SYM_MEM_CLUSTER_SIZE)
		return NULL;

	while (size > s) {
		s <<= 1;
		++i;
	}

	j = i;
	while (!h[j].next) {
		if (s == SYM_MEM_CLUSTER_SIZE) {
			h[j].next = (m_link_p) M_GET_MEM_CLUSTER();
			if (h[j].next)
				h[j].next->next = NULL;
			break;
		}
		++j;
		s <<= 1;
	}
	a = h[j].next;
	if (a) {
		h[j].next = h[j].next->next;
		while (j > i) {
			j -= 1;
			s >>= 1;
			h[j].next = (m_link_p) (a+s);
			h[j].next->next = NULL;
		}
	}
#ifdef DEBUG
	printf("___sym_malloc(%d) = %p\n", size, (void *) a);
#endif
	return a;
}