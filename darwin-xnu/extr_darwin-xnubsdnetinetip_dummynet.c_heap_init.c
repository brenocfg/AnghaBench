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
struct dn_heap_entry {int dummy; } ;
struct dn_heap {int size; struct dn_heap_entry* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct dn_heap_entry*,int /*<<< orphan*/ ) ; 
 int HEAP_INCREMENT ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 struct dn_heap_entry* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct dn_heap_entry*,struct dn_heap_entry*,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
heap_init(struct dn_heap *h, int new_size)
{
    struct dn_heap_entry *p;

    if (h->size >= new_size ) {
	printf("dummynet: heap_init, Bogus call, have %d want %d\n",
		h->size, new_size);
	return 0 ;
    }
    new_size = (new_size + HEAP_INCREMENT ) & ~HEAP_INCREMENT ;
    p = _MALLOC(new_size * sizeof(*p), M_DUMMYNET, M_DONTWAIT );
    if (p == NULL) {
	printf("dummynet: heap_init, resize %d failed\n", new_size );
	return 1 ; /* error */
    }
    if (h->size > 0) {
	bcopy(h->p, p, h->size * sizeof(*p) );
	FREE(h->p, M_DUMMYNET);
    }
    h->p = p ;
    h->size = new_size ;
    return 0 ;
}