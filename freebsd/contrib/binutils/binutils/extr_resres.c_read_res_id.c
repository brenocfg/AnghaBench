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
typedef  int /*<<< orphan*/  unichar ;
struct bin_res_id {struct bin_res_id* id; struct bin_res_id* sig; } ;
typedef  int rc_uint_type ;
struct TYPE_5__ {int length; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {TYPE_1__ n; scalar_t__ id; } ;
struct TYPE_7__ {int named; TYPE_2__ u; } ;
typedef  TYPE_3__ rc_res_id ;

/* Variables and functions */
 scalar_t__ BIN_RES_ID ; 
 int /*<<< orphan*/  read_res_data (int /*<<< orphan*/ *,int*,int,struct bin_res_id*,scalar_t__) ; 
 int /*<<< orphan*/ * read_unistring (int /*<<< orphan*/ *,int*,int,int*) ; 
 scalar_t__ windres_get_16 (int /*<<< orphan*/ *,struct bin_res_id*,int) ; 

__attribute__((used)) static void
read_res_id (windres_bfd *wrbfd, rc_uint_type *off, rc_uint_type omax, rc_res_id *id)
{
  struct bin_res_id bid;
  unsigned short ord;
  unichar *id_s = NULL;
  rc_uint_type len;

  read_res_data (wrbfd, off, omax, &bid, BIN_RES_ID - 2);
  ord = (unsigned short) windres_get_16 (wrbfd, bid.sig, 2);
  if (ord == 0xFFFF)		/* an ordinal id */
    {
      read_res_data (wrbfd, off, omax, bid.id, BIN_RES_ID - 2);
      id->named = 0;
      id->u.id = windres_get_16 (wrbfd, bid.id, 2);
    }
  else
    /* named id */
    {
      off[0] -= 2;
      id_s = read_unistring (wrbfd, off, omax, &len);
      id->named = 1;
      id->u.n.length = len;
      id->u.n.name = id_s;
    }
}