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
struct TYPE_5__ {int length; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ n; void* id; } ;
struct TYPE_7__ {int named; TYPE_2__ u; } ;
typedef  TYPE_3__ rc_res_id ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_unicode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
get_resid (windres_bfd *wrbfd, rc_res_id *id, const bfd_byte *data,
	   rc_uint_type length)
{
  rc_uint_type first;

  if (length < 2)
    toosmall (_("resource ID"));

  first = windres_get_16 (wrbfd, data, 2);
  if (first == 0xffff)
    {
      if (length < 4)
	toosmall (_("resource ID"));
      id->named = 0;
      id->u.id = windres_get_16 (wrbfd, data + 2, 2);
      return 4;
    }
  else
    {
      id->named = 1;
      id->u.n.name = get_unicode (wrbfd, data, length, &id->u.n.length);
      return id->u.n.length * 2 + 2;
    }
}