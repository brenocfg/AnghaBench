#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* page; TYPE_2__* zone; } ;
struct small_page_entry {TYPE_1__ common; struct small_page_entry* next; } ;
struct TYPE_7__ {int pagesize; int page_mask; int quire_size; int dev_zero_fd; scalar_t__ small_page_overhead; int /*<<< orphan*/  debug_file; int /*<<< orphan*/  lg_pagesize; TYPE_2__* zones; } ;
struct TYPE_6__ {char* name; struct small_page_entry* free_pages; } ;

/* Variables and functions */
 int BYTES_PER_ALLOC_BIT ; 
 scalar_t__ FREE_BIN_DELTA ; 
 TYPE_4__ G ; 
 int GGC_PAGE_SIZE ; 
 scalar_t__ MAX_ALIGNMENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PAGE_OVERHEAD ; 
 char* alloc_anon (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  exact_log2 (int) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int getpagesize () ; 
 TYPE_2__ main_zone ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 int /*<<< orphan*/  new_ggc_zone_1 (int /*<<< orphan*/ *,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_zone ; 
 int /*<<< orphan*/  set_page_table_entry (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tree_id_zone ; 
 int /*<<< orphan*/  tree_zone ; 
 struct small_page_entry* xcalloc (int,scalar_t__) ; 

void
init_ggc (void)
{
  /* The allocation size must be greater than BYTES_PER_MARK_BIT, and
     a multiple of both BYTES_PER_ALLOC_BIT and FREE_BIN_DELTA, for
     the current assumptions to hold.  */

  gcc_assert (FREE_BIN_DELTA == MAX_ALIGNMENT);

  /* Set up the main zone by hand.  */
  main_zone.name = "Main zone";
  G.zones = &main_zone;

  /* Allocate the default zones.  */
  new_ggc_zone_1 (&rtl_zone, "RTL zone");
  new_ggc_zone_1 (&tree_zone, "Tree zone");
  new_ggc_zone_1 (&tree_id_zone, "Tree identifier zone");

  G.pagesize = getpagesize();
  G.lg_pagesize = exact_log2 (G.pagesize);
  G.page_mask = ~(G.pagesize - 1);

  /* Require the system page size to be a multiple of GGC_PAGE_SIZE.  */
  gcc_assert ((G.pagesize & (GGC_PAGE_SIZE - 1)) == 0);

  /* Allocate 16 system pages at a time.  */
  G.quire_size = 16 * G.pagesize / GGC_PAGE_SIZE;

  /* Calculate the size of the allocation bitmap and other overhead.  */
  /* Right now we allocate bits for the page header and bitmap.  These
     are wasted, but a little tricky to eliminate.  */
  G.small_page_overhead
    = PAGE_OVERHEAD + (GGC_PAGE_SIZE / BYTES_PER_ALLOC_BIT / 8);
  /* G.small_page_overhead = ROUND_UP (G.small_page_overhead, MAX_ALIGNMENT); */

#ifdef HAVE_MMAP_DEV_ZERO
  G.dev_zero_fd = open ("/dev/zero", O_RDONLY);
  gcc_assert (G.dev_zero_fd != -1);
#endif

#if 0
  G.debug_file = fopen ("ggc-mmap.debug", "w");
  setlinebuf (G.debug_file);
#else
  G.debug_file = stdout;
#endif

#ifdef USING_MMAP
  /* StunOS has an amazing off-by-one error for the first mmap allocation
     after fiddling with RLIMIT_STACK.  The result, as hard as it is to
     believe, is an unaligned page allocation, which would cause us to
     hork badly if we tried to use it.  */
  {
    char *p = alloc_anon (NULL, G.pagesize, &main_zone);
    struct small_page_entry *e;
    if ((size_t)p & (G.pagesize - 1))
      {
	/* How losing.  Discard this one and try another.  If we still
	   can't get something useful, give up.  */

	p = alloc_anon (NULL, G.pagesize, &main_zone);
	gcc_assert (!((size_t)p & (G.pagesize - 1)));
      }

    if (GGC_PAGE_SIZE == G.pagesize)
      {
	/* We have a good page, might as well hold onto it...  */
	e = xcalloc (1, G.small_page_overhead);
	e->common.page = p;
	e->common.zone = &main_zone;
	e->next = main_zone.free_pages;
	set_page_table_entry (e->common.page, &e->common);
	main_zone.free_pages = e;
      }
    else
      {
	munmap (p, G.pagesize);
      }
  }
#endif
}