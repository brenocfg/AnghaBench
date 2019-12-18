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
struct TYPE_5__ {TYPE_3__* group_icon; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
struct TYPE_7__ {struct TYPE_7__* next; void* index; int /*<<< orphan*/  bytes; void* bits; void* planes; void* colors; void* height; void* width; } ;
typedef  TYPE_3__ rc_group_icon ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_GROUP_ICON ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,int) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  windres_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 void* windres_get_8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static rc_res_resource *
bin_to_res_group_icon (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length)
{
  int type, c, i;
  rc_group_icon *first, **pp;
  rc_res_resource *r;

  if (length < 6)
    toosmall (_("group icon header"));

  type = windres_get_16 (wrbfd, data + 2, 2);
  if (type != 1)
    fatal (_("unexpected group icon type %d"), type);

  c = windres_get_16 (wrbfd, data + 4, 2);

  data += 6;
  length -= 6;

  first = NULL;
  pp = &first;

  for (i = 0; i < c; i++)
    {
      rc_group_icon *gi;

      if (length < 14)
	toosmall (_("group icon"));

      gi = (rc_group_icon *) res_alloc (sizeof (rc_group_icon));

      gi->width = windres_get_8 (wrbfd, data, 1);
      gi->height = windres_get_8 (wrbfd, data + 1, 1);
      gi->colors = windres_get_8 (wrbfd, data + 2, 1);
      gi->planes = windres_get_16 (wrbfd, data + 4, 2);
      gi->bits = windres_get_16 (wrbfd, data + 6, 2);
      gi->bytes = windres_get_32 (wrbfd, data + 8, 4);
      gi->index = windres_get_16 (wrbfd, data + 12, 2);

      gi->next = NULL;
      *pp = gi;
      pp = &gi->next;

      data += 14;
      length -= 14;
    }

  r = (rc_res_resource *) res_alloc (sizeof *r);
  r->type = RES_TYPE_GROUP_ICON;
  r->u.group_icon = first;

  return r;
}