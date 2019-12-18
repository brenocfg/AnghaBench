#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee_handle {struct ieee_buf* curbuf; TYPE_1__* current; } ;
struct ieee_buf {size_t c; int* buf; struct ieee_buf* next; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {struct ieee_buf* tail; struct ieee_buf* head; } ;

/* Variables and functions */
 size_t IEEE_BUFSIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
ieee_real_write_byte (struct ieee_handle *info, int b)
{
  if (info->curbuf->c >= IEEE_BUFSIZE)
    {
      struct ieee_buf *n;

      n = (struct ieee_buf *) xmalloc (sizeof *n);
      n->next = NULL;
      n->c = 0;
      if (info->current->head == NULL)
	info->current->head = n;
      else
	info->current->tail->next = n;
      info->current->tail = n;
      info->curbuf = n;
    }

  info->curbuf->buf[info->curbuf->c] = b;
  ++info->curbuf->c;

  return TRUE;
}