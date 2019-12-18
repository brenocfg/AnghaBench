#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int rc_uint_type ;
struct TYPE_5__ {TYPE_3__* cursor; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
struct TYPE_7__ {int length; int /*<<< orphan*/  const* data; void* yhotspot; void* xhotspot; } ;
typedef  TYPE_3__ rc_cursor ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_CURSOR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

rc_res_resource *
bin_to_res_cursor (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length)
{
  rc_cursor *c;
  rc_res_resource *r;

  if (length < 4)
    toosmall (_("cursor"));

  c = (rc_cursor *) res_alloc (sizeof (rc_cursor));
  c->xhotspot = windres_get_16 (wrbfd, data, 2);
  c->yhotspot = windres_get_16 (wrbfd, data + 2, 2);
  c->length = length - 4;
  c->data = data + 4;

  r = (rc_res_resource *) res_alloc (sizeof *r);
  r->type = RES_TYPE_CURSOR;
  r->u.cursor = c;

  return r;
}