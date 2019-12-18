#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int max; int /*<<< orphan*/ ** order; int /*<<< orphan*/  heap; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * keys; } ;
struct TYPE_5__ {int /*<<< orphan*/  userData; scalar_t__ (* memalloc ) (int /*<<< orphan*/ ,size_t) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  TYPE_2__ PriorityQ ;
typedef  int /*<<< orphan*/  PQkey ;

/* Variables and functions */
 scalar_t__ GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Swap (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqHeapInit (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,size_t) ; 

int pqInit( TESSalloc* alloc, PriorityQ *pq )
{
	PQkey **p, **r, **i, **j, *piv;
	struct { PQkey **p, **r; } Stack[50], *top = Stack;
	unsigned int seed = 2016473283;

	/* Create an array of indirect pointers to the keys, so that we
	* the handles we have returned are still valid.
	*/
	/*
	pq->order = (PQkey **)memAlloc( (size_t)
	(pq->size * sizeof(pq->order[0])) );
	*/
	pq->order = (PQkey **)alloc->memalloc( alloc->userData,
										  (size_t)((pq->size+1) * sizeof(pq->order[0])) );
	/* the previous line is a patch to compensate for the fact that IBM */
	/* machines return a null on a malloc of zero bytes (unlike SGI),   */
	/* so we have to put in this defense to guard against a memory      */
	/* fault four lines down. from fossum@austin.ibm.com.               */
	if (pq->order == NULL) return 0;

	p = pq->order;
	r = p + pq->size - 1;
	for( piv = pq->keys, i = p; i <= r; ++piv, ++i ) {
		*i = piv;
	}

	/* Sort the indirect pointers in descending order,
	* using randomized Quicksort
	*/
	top->p = p; top->r = r; ++top;
	while( --top >= Stack ) {
		p = top->p;
		r = top->r;
		while( r > p + 10 ) {
			seed = seed * 1539415821 + 1;
			i = p + seed % (r - p + 1);
			piv = *i;
			*i = *p;
			*p = piv;
			i = p - 1;
			j = r + 1;
			do {
				do { ++i; } while( GT( **i, *piv ));
				do { --j; } while( LT( **j, *piv ));
				Swap( i, j );
			} while( i < j );
			Swap( i, j ); /* Undo last swap */
			if( i - p < r - j ) {
				top->p = j+1; top->r = r; ++top;
				r = i-1;
			} else {
				top->p = p; top->r = i-1; ++top;
				p = j+1;
			}
		}
		/* Insertion sort small lists */
		for( i = p+1; i <= r; ++i ) {
			piv = *i;
			for( j = i; j > p && LT( **(j-1), *piv ); --j ) {
				*j = *(j-1);
			}
			*j = piv;
		}
	}
	pq->max = pq->size;
	pq->initialized = TRUE;
	pqHeapInit( pq->heap );  /* always succeeds */

#ifndef NDEBUG
	p = pq->order;
	r = p + pq->size - 1;
	for( i = p; i < r; ++i ) {
		assert( LEQ( **(i+1), **i ));
	}
#endif

	return 1;
}