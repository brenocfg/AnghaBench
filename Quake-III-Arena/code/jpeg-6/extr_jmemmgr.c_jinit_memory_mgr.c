#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* my_mem_ptr ;
typedef  TYPE_3__* j_common_ptr ;
struct TYPE_12__ {TYPE_1__* mem; } ;
struct TYPE_10__ {long max_memory_to_use; int /*<<< orphan*/  self_destruct; int /*<<< orphan*/  free_pool; int /*<<< orphan*/  access_virt_barray; int /*<<< orphan*/  access_virt_sarray; int /*<<< orphan*/  realize_virt_arrays; int /*<<< orphan*/  request_virt_barray; int /*<<< orphan*/  request_virt_sarray; int /*<<< orphan*/  alloc_barray; int /*<<< orphan*/  alloc_sarray; int /*<<< orphan*/  alloc_large; int /*<<< orphan*/  alloc_small; } ;
struct TYPE_11__ {long total_space_allocated; TYPE_1__ pub; int /*<<< orphan*/ * virt_barray_list; int /*<<< orphan*/ * virt_sarray_list; int /*<<< orphan*/ ** large_list; int /*<<< orphan*/ ** small_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_TYPE ; 
 int /*<<< orphan*/  ERREXIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERR_BAD_ALIGN_TYPE ; 
 int /*<<< orphan*/  JERR_BAD_ALLOC_CHUNK ; 
 int /*<<< orphan*/  JERR_OUT_OF_MEMORY ; 
 int JPOOL_NUMPOOLS ; 
 int JPOOL_PERMANENT ; 
 long MAX_ALLOC_CHUNK ; 
 long SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_virt_barray ; 
 int /*<<< orphan*/  access_virt_sarray ; 
 int /*<<< orphan*/  alloc_barray ; 
 int /*<<< orphan*/  alloc_large ; 
 int /*<<< orphan*/  alloc_sarray ; 
 int /*<<< orphan*/  alloc_small ; 
 int /*<<< orphan*/  free_pool ; 
 char* getenv (char*) ; 
 scalar_t__ jpeg_get_small (TYPE_3__*,long) ; 
 long jpeg_mem_init (TYPE_3__*) ; 
 int /*<<< orphan*/  jpeg_mem_term (TYPE_3__*) ; 
 int /*<<< orphan*/  my_memory_mgr ; 
 int /*<<< orphan*/  realize_virt_arrays ; 
 int /*<<< orphan*/  request_virt_barray ; 
 int /*<<< orphan*/  request_virt_sarray ; 
 int /*<<< orphan*/  self_destruct ; 
 scalar_t__ sscanf (char*,char*,long*,char*) ; 

void
jinit_memory_mgr (j_common_ptr cinfo)
{
  my_mem_ptr mem;
  long max_to_use;
  int pool;
  size_t test_mac;

  cinfo->mem = NULL;		/* for safety if init fails */

  /* Check for configuration errors.
   * SIZEOF(ALIGN_TYPE) should be a power of 2; otherwise, it probably
   * doesn't reflect any real hardware alignment requirement.
   * The test is a little tricky: for X>0, X and X-1 have no one-bits
   * in common if and only if X is a power of 2, ie has only one one-bit.
   * Some compilers may give an "unreachable code" warning here; ignore it.
   */
  if ((SIZEOF(ALIGN_TYPE) & (SIZEOF(ALIGN_TYPE)-1)) != 0)
    ERREXIT(cinfo, JERR_BAD_ALIGN_TYPE);
  /* MAX_ALLOC_CHUNK must be representable as type size_t, and must be
   * a multiple of SIZEOF(ALIGN_TYPE).
   * Again, an "unreachable code" warning may be ignored here.
   * But a "constant too large" warning means you need to fix MAX_ALLOC_CHUNK.
   */
  test_mac = (size_t) MAX_ALLOC_CHUNK;
  if ((long) test_mac != MAX_ALLOC_CHUNK ||
      (MAX_ALLOC_CHUNK % SIZEOF(ALIGN_TYPE)) != 0)
    ERREXIT(cinfo, JERR_BAD_ALLOC_CHUNK);

  max_to_use = jpeg_mem_init(cinfo); /* system-dependent initialization */

  /* Attempt to allocate memory manager's control block */
  mem = (my_mem_ptr) jpeg_get_small(cinfo, SIZEOF(my_memory_mgr));

  if (mem == NULL) {
    jpeg_mem_term(cinfo);	/* system-dependent cleanup */
    ERREXIT1(cinfo, JERR_OUT_OF_MEMORY, 0);
  }

  /* OK, fill in the method pointers */
  mem->pub.alloc_small = alloc_small;
  mem->pub.alloc_large = alloc_large;
  mem->pub.alloc_sarray = alloc_sarray;
  mem->pub.alloc_barray = alloc_barray;
  mem->pub.request_virt_sarray = request_virt_sarray;
  mem->pub.request_virt_barray = request_virt_barray;
  mem->pub.realize_virt_arrays = realize_virt_arrays;
  mem->pub.access_virt_sarray = access_virt_sarray;
  mem->pub.access_virt_barray = access_virt_barray;
  mem->pub.free_pool = free_pool;
  mem->pub.self_destruct = self_destruct;

  /* Initialize working state */
  mem->pub.max_memory_to_use = max_to_use;

  for (pool = JPOOL_NUMPOOLS-1; pool >= JPOOL_PERMANENT; pool--) {
    mem->small_list[pool] = NULL;
    mem->large_list[pool] = NULL;
  }
  mem->virt_sarray_list = NULL;
  mem->virt_barray_list = NULL;

  mem->total_space_allocated = SIZEOF(my_memory_mgr);

  /* Declare ourselves open for business */
  cinfo->mem = & mem->pub;

  /* Check for an environment variable JPEGMEM; if found, override the
   * default max_memory setting from jpeg_mem_init.  Note that the
   * surrounding application may again override this value.
   * If your system doesn't support getenv(), define NO_GETENV to disable
   * this feature.
   */
#ifndef NO_GETENV
  { char * memenv;

    if ((memenv = getenv("JPEGMEM")) != NULL) {
      char ch = 'x';

      if (sscanf(memenv, "%ld%c", &max_to_use, &ch) > 0) {
	if (ch == 'm' || ch == 'M')
	  max_to_use *= 1000L;
	mem->pub.max_memory_to_use = max_to_use * 1000L;
      }
    }
  }
#endif

}