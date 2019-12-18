#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_cursor {int /*<<< orphan*/  yhotspot; int /*<<< orphan*/  xhotspot; } ;
typedef  scalar_t__ rc_uint_type ;
struct TYPE_3__ {scalar_t__ length; struct bin_cursor* data; int /*<<< orphan*/  yhotspot; int /*<<< orphan*/  xhotspot; } ;
typedef  TYPE_1__ rc_cursor ;

/* Variables and functions */
 scalar_t__ BIN_CURSOR_SIZE ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_cursor*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_cursor (windres_bfd *wrbfd, rc_uint_type off, const rc_cursor *c)
{
  if (wrbfd)
    {
      struct bin_cursor bc;

      windres_put_16 (wrbfd, bc.xhotspot, c->xhotspot);
      windres_put_16 (wrbfd, bc.yhotspot, c->yhotspot);
      set_windres_bfd_content (wrbfd, &bc, off, BIN_CURSOR_SIZE);
      if (c->length)
	set_windres_bfd_content (wrbfd, c->data, off + BIN_CURSOR_SIZE, c->length);
    }
  off = (off + BIN_CURSOR_SIZE + (rc_uint_type) c->length);
  return off;
}