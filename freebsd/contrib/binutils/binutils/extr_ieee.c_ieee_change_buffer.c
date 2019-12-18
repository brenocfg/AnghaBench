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
struct ieee_handle {struct ieee_buf* curbuf; struct ieee_buflist* current; } ;
struct ieee_buflist {struct ieee_buf* tail; struct ieee_buf* head; } ;
struct ieee_buf {scalar_t__ c; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
ieee_change_buffer (struct ieee_handle *info, struct ieee_buflist *buflist)
{
  if (buflist->head == NULL)
    {
      struct ieee_buf *buf;

      buf = (struct ieee_buf *) xmalloc (sizeof *buf);
      buf->next = NULL;
      buf->c = 0;
      buflist->head = buf;
      buflist->tail = buf;
    }

  info->current = buflist;
  info->curbuf = buflist->tail;

  return TRUE;
}