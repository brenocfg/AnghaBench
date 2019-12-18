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
struct file {struct IDAT* idat; int /*<<< orphan*/ * chunk; int /*<<< orphan*/  (* alloc ) (struct file* const,int /*<<< orphan*/ ) ;TYPE_2__* global; } ;
struct IDAT {TYPE_2__* global; TYPE_1__* idat_list_tail; TYPE_1__* idat_list_head; struct file* file; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ idat_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct IDAT) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct file* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
IDAT_init(struct IDAT * const idat, struct file * const file)
   /* When the chunk is png_IDAT instantiate an IDAT control structure in place
    * of a chunk control structure.  The IDAT will instantiate a chunk control
    * structure using the file alloc routine.
    *
    * NOTE: this routine must only be called from the file alloc routine!
    */
{
   assert(file->chunk == NULL);
   assert(file->idat == NULL);

   CLEAR(*idat);

   idat->file = file;
   idat->global = file->global;

   /* Initialize the tail to the pre-allocated buffer and set the count to 0
    * (empty.)
    */
   idat->global->idat_cache.count = 0;
   idat->idat_list_head = idat->idat_list_tail = &idat->global->idat_cache;

   /* Now the chunk.  The allocator calls the initializer of the new chunk and
    * stores the result in file->chunk:
    */
   file->alloc(file, 0/*chunk*/);
   assert(file->chunk != NULL);

   /* And store this for cleanup (and to check for double alloc or failure to
    * free.)
    */
   file->idat = idat;
}