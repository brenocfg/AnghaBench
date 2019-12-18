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
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_3__ {scalar_t__ data; scalar_t__ length; scalar_t__ yhotspot; scalar_t__ xhotspot; } ;
typedef  TYPE_1__ rc_cursor ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_rc_datablock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_rc_cursor (FILE *e, const rc_cursor *cursor)
{
  fprintf (e, "BEGIN\n");
  indent (e, 2);
  fprintf (e, " 0x%x, 0x%x,\t/* Hotspot x: %d, y: %d.  */\n",
	   (unsigned int) cursor->xhotspot, (unsigned int) cursor->yhotspot,
	   (int) cursor->xhotspot, (int) cursor->yhotspot);
  write_rc_datablock (e, (rc_uint_type) cursor->length, (const bfd_byte *) cursor->data,
  		      0, 0, 0);
  fprintf (e, "END\n");
}