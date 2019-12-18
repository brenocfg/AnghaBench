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
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_toolbar {struct bin_toolbar* nitems; struct bin_toolbar* button_height; struct bin_toolbar* button_width; } ;
typedef  int rc_uint_type ;
struct TYPE_6__ {int id; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__ id; } ;
typedef  TYPE_3__ rc_toolbar_item ;
struct TYPE_9__ {int button_width; int button_height; int nitems; TYPE_3__* items; } ;
typedef  TYPE_4__ rc_toolbar ;
typedef  struct bin_toolbar bfd_byte ;

/* Variables and functions */
 int BIN_TOOLBAR_SIZE ; 
 scalar_t__ reswr_alloc (int) ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_toolbar*,int,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,struct bin_toolbar*,int) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_toolbar (windres_bfd *wrbfd, rc_uint_type off, rc_toolbar *tb)
{
  if (wrbfd)
    {
      struct bin_toolbar bt;
      windres_put_32 (wrbfd, bt.button_width, tb->button_width);
      windres_put_32 (wrbfd, bt.button_height, tb->button_height);
      windres_put_32 (wrbfd, bt.nitems, tb->nitems);
      set_windres_bfd_content (wrbfd, &bt, off, BIN_TOOLBAR_SIZE);
      if (tb->nitems > 0)
	{
	  rc_toolbar_item *it;
	  bfd_byte *ids;
	  rc_uint_type i = 0;

	  ids = (bfd_byte *) reswr_alloc (tb->nitems * 4);
	  it=tb->items;
	  while(it != NULL)
	    {
	      windres_put_32 (wrbfd, ids + i, it->id.u.id);
	      i += 4;
	      it = it->next;
	    }
	  set_windres_bfd_content (wrbfd, ids, off + BIN_TOOLBAR_SIZE, i);
 	}
    }
  off += BIN_TOOLBAR_SIZE + tb->nitems * 4;

  return off;
}