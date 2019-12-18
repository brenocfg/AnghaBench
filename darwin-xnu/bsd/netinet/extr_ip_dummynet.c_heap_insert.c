#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dn_heap_entry {int dummy; } ;
struct dn_heap {int elements; int size; TYPE_1__* p; } ;
typedef  void* dn_key ;
struct TYPE_3__ {void* key; void* object; } ;

/* Variables and functions */
 scalar_t__ DN_KEY_LT (void*,void*) ; 
 int HEAP_FATHER (int) ; 
 int /*<<< orphan*/  HEAP_SWAP (TYPE_1__,TYPE_1__,struct dn_heap_entry) ; 
 int /*<<< orphan*/  SET_OFFSET (struct dn_heap*,int) ; 
 scalar_t__ heap_init (struct dn_heap*,int) ; 

__attribute__((used)) static int
heap_insert(struct dn_heap *h, dn_key key1, void *p)
{
    int son = h->elements ;

    if (p == NULL)	/* data already there, set starting point */
	son = key1 ;
    else {		/* insert new element at the end, possibly resize */
	son = h->elements ;
	if (son == h->size) /* need resize... */
	    if (heap_init(h, h->elements+1) )
		return 1 ; /* failure... */
	h->p[son].object = p ;
	h->p[son].key = key1 ;
	h->elements++ ;
    }
    while (son > 0) {				/* bubble up */
	int father = HEAP_FATHER(son) ;
	struct dn_heap_entry tmp  ;

	if (DN_KEY_LT( h->p[father].key, h->p[son].key ) )
	    break ; /* found right position */
	/* son smaller than father, swap and repeat */
	HEAP_SWAP(h->p[son], h->p[father], tmp) ;
	SET_OFFSET(h, son);
	son = father ;
    }
    SET_OFFSET(h, son);
    return 0 ;
}