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
typedef  scalar_t__ mchunkptr ;

/* Variables and functions */
 int /*<<< orphan*/  MALLOC_FAILURE_ACTION ; 
 size_t MAX_REQUEST ; 
 int /*<<< orphan*/  POSTACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_inuse_chunk (int /*<<< orphan*/ ,scalar_t__) ; 
 void* chunk2mem (scalar_t__) ; 
 size_t chunksize (scalar_t__) ; 
 void* dlmalloc (size_t) ; 
 int /*<<< orphan*/  gm ; 
 int /*<<< orphan*/  internal_free (int /*<<< orphan*/ ,void*) ; 
 void* internal_malloc (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ mem2chunk (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 size_t overhead_for (scalar_t__) ; 
 size_t request2size (size_t) ; 
 scalar_t__ try_realloc_chunk (int /*<<< orphan*/ ,scalar_t__,size_t,int) ; 

void* dlrealloc(void* oldmem, size_t bytes) {
    void* mem = 0;
    if (oldmem == 0) {
        mem = dlmalloc(bytes);
    }
    else if (bytes >= MAX_REQUEST) {
        MALLOC_FAILURE_ACTION;
    }
#ifdef REALLOC_ZERO_BYTES_FREES
    else if (bytes == 0) {
        dlfree(oldmem);
    }
#endif /* REALLOC_ZERO_BYTES_FREES */
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
            mchunkptr newp = try_realloc_chunk(m, oldp, nb, 1);
            POSTACTION(m);
            if (newp != 0) {
                check_inuse_chunk(m, newp);
                mem = chunk2mem(newp);
#if __EMSCRIPTEN__
                /* XXX Emscripten Tracing API. */
                emscripten_trace_record_reallocation(oldmem, mem, bytes);
#endif
            }
            else {
                mem = internal_malloc(m, bytes);
                if (mem != 0) {
                    size_t oc = chunksize(oldp) - overhead_for(oldp);
                    memcpy(mem, oldmem, (oc < bytes)? oc : bytes);
                    internal_free(m, oldmem);
                }
            }
        }
    }
    return mem;
}