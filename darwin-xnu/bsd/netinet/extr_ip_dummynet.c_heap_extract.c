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
typedef  int /*<<< orphan*/  uint64_t ;
struct dn_heap {int elements; scalar_t__ offset; TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ DN_KEY_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HEAP_LEFT (int) ; 
 int /*<<< orphan*/  RESET_OFFSET (struct dn_heap*,int) ; 
 int /*<<< orphan*/  SET_OFFSET (struct dn_heap*,int) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct dn_heap*) ; 
 int /*<<< orphan*/  heap_insert (struct dn_heap*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
heap_extract(struct dn_heap *h, void *obj)
{
    int child, father, maxelt = h->elements - 1 ;

    if (maxelt < 0) {
	printf("dummynet: warning, extract from empty heap 0x%llx\n",
	    (uint64_t)VM_KERNEL_ADDRPERM(h));
	return ;
    }
    father = 0 ; /* default: move up smallest child */
    if (obj != NULL) { /* extract specific element, index is at offset */
	if (h->offset <= 0)
	    panic("dummynet: heap_extract from middle not supported on this heap!!!\n");
	father = *((int *)((char *)obj + h->offset)) ;
	if (father < 0 || father >= h->elements) {
	    printf("dummynet: heap_extract, father %d out of bound 0..%d\n",
		father, h->elements);
	    panic("dummynet: heap_extract");
	}
    }
    RESET_OFFSET(h, father);
    child = HEAP_LEFT(father) ;		/* left child */
    while (child <= maxelt) {		/* valid entry */
	if (child != maxelt && DN_KEY_LT(h->p[child+1].key, h->p[child].key) )
	    child = child+1 ;		/* take right child, otherwise left */
	h->p[father] = h->p[child] ;
	SET_OFFSET(h, father);
	father = child ;
	child = HEAP_LEFT(child) ;   /* left child for next loop */
    }
    h->elements-- ;
    if (father != maxelt) {
	/*
	 * Fill hole with last entry and bubble up, reusing the insert code
	 */
	h->p[father] = h->p[maxelt] ;
	heap_insert(h, father, NULL); /* this one cannot fail */
    }
}