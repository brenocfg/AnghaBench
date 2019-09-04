#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;
struct TYPE_12__ {int /*<<< orphan*/  topsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION_ERROR_ACTION (TYPE_1__*) ; 
 int /*<<< orphan*/  POSTACTION (TYPE_1__*) ; 
 int /*<<< orphan*/  PREACTION (TYPE_1__*) ; 
 scalar_t__ RTCHECK (int) ; 
 int /*<<< orphan*/  check_inuse_chunk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* chunk2mem (int /*<<< orphan*/ ) ; 
 size_t chunksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispose_chunk (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mem2chunk (void*) ; 
 int /*<<< orphan*/  next_chunk (int /*<<< orphan*/ ) ; 
 scalar_t__ ok_address (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ok_inuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inuse (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ should_trim (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_trim (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t internal_bulk_free(mstate m, void* array[], size_t nelem) {
    size_t unfreed = 0;
    if (!PREACTION(m)) {
        void** a;
        void** fence = &(array[nelem]);
        for (a = array; a != fence; ++a) {
            void* mem = *a;
            if (mem != 0) {
                mchunkptr p = mem2chunk(mem);
                size_t psize = chunksize(p);
#if FOOTERS
                if (get_mstate_for(p) != m) {
                    ++unfreed;
                    continue;
                }
#endif
                check_inuse_chunk(m, p);
                *a = 0;
                if (RTCHECK(ok_address(m, p) && ok_inuse(p))) {
                    void ** b = a + 1; /* try to merge with next chunk */
                    mchunkptr next = next_chunk(p);
                    if (b != fence && *b == chunk2mem(next)) {
                        size_t newsize = chunksize(next) + psize;
                        set_inuse(m, p, newsize);
                        *b = chunk2mem(p);
                    }
                    else
                        dispose_chunk(m, p, psize);
                }
                else {
                    CORRUPTION_ERROR_ACTION(m);
                    break;
                }
            }
        }
        if (should_trim(m, m->topsize))
            sys_trim(m, 0);
        POSTACTION(m);
    }
    return unfreed;
}