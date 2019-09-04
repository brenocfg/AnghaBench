#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mflags; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {scalar_t__ magic; size_t granularity; size_t page_size; int default_mflags; int /*<<< orphan*/  trim_threshold; int /*<<< orphan*/  mmap_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  ACQUIRE_MALLOC_GLOBAL_LOCK () ; 
 scalar_t__ DEFAULT_GRANULARITY ; 
 int /*<<< orphan*/  DEFAULT_MMAP_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_TRIM_THRESHOLD ; 
 int /*<<< orphan*/  INITIAL_LOCK (int /*<<< orphan*/ *) ; 
 size_t MALLOC_ALIGNMENT ; 
 scalar_t__ MAX_SIZE_T ; 
 size_t MCHUNK_SIZE ; 
 scalar_t__ MIN_CHUNK_SIZE ; 
 int /*<<< orphan*/  RELEASE_MALLOC_GLOBAL_LOCK () ; 
 size_t SIZE_T_ONE ; 
 int USE_LOCK_BIT ; 
 int USE_MMAP_BIT ; 
 int USE_NONCONTIGUOUS_BIT ; 
 TYPE_2__* gm ; 
 size_t malloc_getpagesize ; 
 TYPE_1__ mparams ; 
 size_t time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_mparams(void) {
#ifdef NEED_GLOBAL_LOCK_INIT
    if (malloc_global_mutex_status <= 0)
        init_malloc_global_mutex();
#endif
    
    ACQUIRE_MALLOC_GLOBAL_LOCK();
    if (mparams.magic == 0) {
        size_t magic;
        size_t psize;
        size_t gsize;
        
#ifndef WIN32
        psize = malloc_getpagesize;
        gsize = ((DEFAULT_GRANULARITY != 0)? DEFAULT_GRANULARITY : psize);
#else /* WIN32 */
        {
            SYSTEM_INFO system_info;
            GetSystemInfo(&system_info);
            psize = system_info.dwPageSize;
            gsize = ((DEFAULT_GRANULARITY != 0)?
                     DEFAULT_GRANULARITY : system_info.dwAllocationGranularity);
        }
#endif /* WIN32 */
        
        /* Sanity-check configuration:
         size_t must be unsigned and as wide as pointer type.
         ints must be at least 4 bytes.
         alignment must be at least 8.
         Alignment, min chunk size, and page size must all be powers of 2.
         */
        if ((sizeof(size_t) != sizeof(char*)) ||
            (MAX_SIZE_T < MIN_CHUNK_SIZE)  ||
            (sizeof(int) < 4)  ||
            (MALLOC_ALIGNMENT < (size_t)8U) ||
            ((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT-SIZE_T_ONE)) != 0) ||
            ((MCHUNK_SIZE      & (MCHUNK_SIZE-SIZE_T_ONE))      != 0) ||
            ((gsize            & (gsize-SIZE_T_ONE))            != 0) ||
            ((psize            & (psize-SIZE_T_ONE))            != 0))
            ABORT;
        mparams.granularity = gsize;
        mparams.page_size = psize;
        mparams.mmap_threshold = DEFAULT_MMAP_THRESHOLD;
        mparams.trim_threshold = DEFAULT_TRIM_THRESHOLD;
#if MORECORE_CONTIGUOUS
        mparams.default_mflags = USE_LOCK_BIT|USE_MMAP_BIT;
#else  /* MORECORE_CONTIGUOUS */
        mparams.default_mflags = USE_LOCK_BIT|USE_MMAP_BIT|USE_NONCONTIGUOUS_BIT;
#endif /* MORECORE_CONTIGUOUS */
        
#if !ONLY_MSPACES
        /* Set up lock for main malloc area */
        gm->mflags = mparams.default_mflags;
        (void)INITIAL_LOCK(&gm->mutex);
#endif
#if LOCK_AT_FORK
        pthread_atfork(&pre_fork, &post_fork_parent, &post_fork_child);
#endif
        
        {
#if USE_DEV_RANDOM
            int fd;
            unsigned char buf[sizeof(size_t)];
            /* Try to use /dev/urandom, else fall back on using time */
            if ((fd = open("/dev/urandom", O_RDONLY)) >= 0 &&
                read(fd, buf, sizeof(buf)) == sizeof(buf)) {
                magic = *((size_t *) buf);
                close(fd);
            }
            else
#endif /* USE_DEV_RANDOM */
#ifdef WIN32
                magic = (size_t)(GetTickCount() ^ (size_t)0x55555555U);
#elif defined(LACKS_TIME_H) || defined(__EMSCRIPTEN__)
            magic = (size_t)&magic ^ (size_t)0x55555555U;
#else
            magic = (size_t)(time(0) ^ (size_t)0x55555555U);
#endif
            magic |= (size_t)8U;    /* ensure nonzero */
            magic &= ~(size_t)7U;   /* improve chances of fault for bad values */
            /* Until memory modes commonly available, use volatile-write */
            (*(volatile size_t *)(&(mparams.magic))) = magic;
        }
    }
    
    RELEASE_MALLOC_GLOBAL_LOCK();
    return 1;
}