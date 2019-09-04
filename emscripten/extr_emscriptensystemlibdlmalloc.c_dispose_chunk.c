#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* mchunkptr ;
struct TYPE_24__ {size_t prev_foot; int head; } ;
struct TYPE_23__ {size_t footprint; size_t dvsize; size_t topsize; TYPE_2__* dv; TYPE_2__* top; } ;

/* Variables and functions */
 scalar_t__ CALL_MUNMAP (char*,size_t) ; 
 int /*<<< orphan*/  CORRUPTION_ERROR_ACTION (TYPE_1__*) ; 
 int INUSE_BITS ; 
 scalar_t__ MMAP_FOOT_PAD ; 
 size_t PINUSE_BIT ; 
 scalar_t__ RTCHECK (int /*<<< orphan*/ ) ; 
 TYPE_2__* chunk_minus_offset (TYPE_2__*,size_t) ; 
 TYPE_2__* chunk_plus_offset (TYPE_2__*,size_t) ; 
 size_t chunksize (TYPE_2__*) ; 
 int /*<<< orphan*/  cinuse (TYPE_2__*) ; 
 int /*<<< orphan*/  insert_chunk (TYPE_1__*,TYPE_2__*,size_t) ; 
 scalar_t__ is_mmapped (TYPE_2__*) ; 
 int /*<<< orphan*/  ok_address (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pinuse (TYPE_2__*) ; 
 int /*<<< orphan*/  set_free_with_pinuse (TYPE_2__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_free_chunk (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  unlink_chunk (TYPE_1__*,TYPE_2__*,size_t) ; 

__attribute__((used)) static void dispose_chunk(mstate m, mchunkptr p, size_t psize) {
    mchunkptr next = chunk_plus_offset(p, psize);
    if (!pinuse(p)) {
        mchunkptr prev;
        size_t prevsize = p->prev_foot;
        if (is_mmapped(p)) {
            psize += prevsize + MMAP_FOOT_PAD;
            if (CALL_MUNMAP((char*)p - prevsize, psize) == 0)
                m->footprint -= psize;
            return;
        }
        prev = chunk_minus_offset(p, prevsize);
        psize += prevsize;
        p = prev;
        if (RTCHECK(ok_address(m, prev))) { /* consolidate backward */
            if (p != m->dv) {
                unlink_chunk(m, p, prevsize);
            }
            else if ((next->head & INUSE_BITS) == INUSE_BITS) {
                m->dvsize = psize;
                set_free_with_pinuse(p, psize, next);
                return;
            }
        }
        else {
            CORRUPTION_ERROR_ACTION(m);
            return;
        }
    }
    if (RTCHECK(ok_address(m, next))) {
        if (!cinuse(next)) {  /* consolidate forward */
            if (next == m->top) {
                size_t tsize = m->topsize += psize;
                m->top = p;
                p->head = tsize | PINUSE_BIT;
                if (p == m->dv) {
                    m->dv = 0;
                    m->dvsize = 0;
                }
                return;
            }
            else if (next == m->dv) {
                size_t dsize = m->dvsize += psize;
                m->dv = p;
                set_size_and_pinuse_of_free_chunk(p, dsize);
                return;
            }
            else {
                size_t nsize = chunksize(next);
                psize += nsize;
                unlink_chunk(m, next, nsize);
                set_size_and_pinuse_of_free_chunk(p, psize);
                if (p == m->dv) {
                    m->dvsize = psize;
                    return;
                }
            }
        }
        else {
            set_free_with_pinuse(p, psize, next);
        }
        insert_chunk(m, p, psize);
    }
    else {
        CORRUPTION_ERROR_ACTION(m);
    }
}