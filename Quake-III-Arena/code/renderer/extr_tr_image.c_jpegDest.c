#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct jpeg_destination_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  my_destination_mgr ;
typedef  TYPE_3__* my_dest_ptr ;
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_9__ {struct jpeg_destination_mgr* dest; TYPE_2__* mem; } ;
struct TYPE_6__ {int /*<<< orphan*/  term_destination; int /*<<< orphan*/  empty_output_buffer; int /*<<< orphan*/  init_destination; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/ * outfile; TYPE_1__ pub; } ;
struct TYPE_7__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  JPOOL_PERMANENT ; 
 int /*<<< orphan*/  empty_output_buffer ; 
 int /*<<< orphan*/  init_destination ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  term_destination ; 

void jpegDest (j_compress_ptr cinfo, byte* outfile, int size)
{
  my_dest_ptr dest;

  /* The destination object is made permanent so that multiple JPEG images
   * can be written to the same file without re-executing jpeg_stdio_dest.
   * This makes it dangerous to use this manager and a different destination
   * manager serially with the same JPEG object, because their private object
   * sizes may be different.  Caveat programmer.
   */
  if (cinfo->dest == NULL) {	/* first time for this JPEG object? */
    cinfo->dest = (struct jpeg_destination_mgr *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				  sizeof(my_destination_mgr));
  }

  dest = (my_dest_ptr) cinfo->dest;
  dest->pub.init_destination = init_destination;
  dest->pub.empty_output_buffer = empty_output_buffer;
  dest->pub.term_destination = term_destination;
  dest->outfile = outfile;
  dest->size = size;
}