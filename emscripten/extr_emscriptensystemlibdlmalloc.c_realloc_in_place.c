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
typedef  int /*<<< orphan*/  mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;

/* Variables and functions */
 int /*<<< orphan*/  MALLOC_FAILURE_ACTION ; 
 size_t MAX_REQUEST ; 
 int /*<<< orphan*/  POSTACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_inuse_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm ; 
 int /*<<< orphan*/  mem2chunk (void*) ; 
 size_t request2size (size_t) ; 
 int /*<<< orphan*/  try_realloc_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void* dlrealloc_in_place(void* oldmem, size_t bytes) {
    void* mem = 0;
    if (oldmem != 0) {
        if (bytes >= MAX_REQUEST) {
            MALLOC_FAILURE_ACTION;
        }
        else {
            size_t nb = request2size(bytes);
            mchunkptr oldp = mem2chunk(oldmem);
#if ! FOOTERS
            mstate m = gm;
#else /* FOOTERS */
            mstate m = get_mstate_for(oldp);
            if (!ok_magic(m)) {
                USAGE_ERROR_ACTION(m, oldmem);
                return 0;
            }
#endif /* FOOTERS */
            if (!PREACTION(m)) {
                mchunkptr newp = try_realloc_chunk(m, oldp, nb, 0);
                POSTACTION(m);
                if (newp == oldp) {
                    check_inuse_chunk(m, newp);
                    mem = oldmem;
                }
            }
        }
    }
#if __EMSCRIPTEN__
    /* XXX Emscripten Tracing API. */
    emscripten_trace_record_reallocation(oldmem, mem, bytes);
#endif
    return mem;
}