#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ps_b; } ;
struct TYPE_7__ {TYPE_2__* pb_buf; } ;
struct TYPE_8__ {int sb_flags; TYPE_1__ sb_pb; TYPE_3__* sb_ps; } ;
typedef  TYPE_2__ PE_SecBuf ;
typedef  TYPE_3__ PE_Scn ;

/* Variables and functions */
 int LIBPE_F_BUFFER_MALLOCED ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PE_SecBuf ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sb_next ; 

void
libpe_release_buffer(PE_SecBuf *sb)
{
	PE_Scn *ps;

	assert(sb != NULL);

	ps = sb->sb_ps;

	STAILQ_REMOVE(&ps->ps_b, sb, _PE_SecBuf, sb_next);

	if (sb->sb_flags & LIBPE_F_BUFFER_MALLOCED)
		free(sb->sb_pb.pb_buf);

	free(sb);
}