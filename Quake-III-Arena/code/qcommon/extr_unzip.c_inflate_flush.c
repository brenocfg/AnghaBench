#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  scalar_t__ uInt ;
struct TYPE_6__ {int /*<<< orphan*/ * read; int /*<<< orphan*/  check; int /*<<< orphan*/  (* checkfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;int /*<<< orphan*/ * write; int /*<<< orphan*/ * window; int /*<<< orphan*/ * end; } ;
typedef  TYPE_2__ inflate_blocks_statef ;
struct TYPE_5__ {scalar_t__ avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  adler; int /*<<< orphan*/  total_out; } ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_NULL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int Z_OK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zmemcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int inflate_flush(inflate_blocks_statef *s, z_streamp z, int r)
{
  uInt n;
  Byte *p;
  Byte *q;

  /* static copies of source and destination pointers */
  p = z->next_out;
  q = s->read;

  /* compute number of bytes to copy as as end of window */
  n = (uInt)((q <= s->write ? s->write : s->end) - q);
  if (n > z->avail_out) n = z->avail_out;
  if (n && r == Z_BUF_ERROR) r = Z_OK;

  /* update counters */
  z->avail_out -= n;
  z->total_out += n;

  /* update check information */
  if (s->checkfn != Z_NULL)
    z->adler = s->check = (*s->checkfn)(s->check, q, n);

  /* copy as as end of window */
  zmemcpy(p, q, n);
  p += n;
  q += n;

  /* see if more to copy at beginning of window */
  if (q == s->end)
  {
    /* wrap pointers */
    q = s->window;
    if (s->write == s->end)
      s->write = s->window;

    /* compute bytes to copy */
    n = (uInt)(s->write - q);
    if (n > z->avail_out) n = z->avail_out;
    if (n && r == Z_BUF_ERROR) r = Z_OK;

    /* update counters */
    z->avail_out -= n;
    z->total_out += n;

    /* update check information */
    if (s->checkfn != Z_NULL)
      z->adler = s->check = (*s->checkfn)(s->check, q, n);

    /* copy */
    zmemcpy(p, q, n);
    p += n;
    q += n;
  }

  /* update pointers */
  z->next_out = p;
  s->read = q;

  /* done */
  return r;
}