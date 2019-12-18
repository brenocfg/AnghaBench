#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct v4l2_timecode {scalar_t__ userbits; int /*<<< orphan*/  frames; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  seconds; int /*<<< orphan*/  minutes; int /*<<< orphan*/  hours; } ;
struct TYPE_4__ {int /*<<< orphan*/  userptr; } ;
struct TYPE_3__ {int tv_sec; scalar_t__ tv_usec; } ;
struct v4l2_buffer {int /*<<< orphan*/  length; TYPE_2__ m; int /*<<< orphan*/  memory; int /*<<< orphan*/  sequence; int /*<<< orphan*/  field; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  type; int /*<<< orphan*/  index; TYPE_1__ timestamp; struct v4l2_timecode timecode; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  dbgarg (unsigned int,char*,int,int,int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgarg2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_memory_names ; 
 int /*<<< orphan*/  v4l2_type_names ; 

__attribute__((used)) static void dbgbuf(unsigned int cmd, struct video_device *vfd,
					struct v4l2_buffer *p)
{
	struct v4l2_timecode *tc = &p->timecode;

	dbgarg(cmd, "%02ld:%02d:%02d.%08ld index=%d, type=%s, "
		"bytesused=%d, flags=0x%08d, "
		"field=%0d, sequence=%d, memory=%s, offset/userptr=0x%08lx, length=%d\n",
			p->timestamp.tv_sec / 3600,
			(int)(p->timestamp.tv_sec / 60) % 60,
			(int)(p->timestamp.tv_sec % 60),
			(long)p->timestamp.tv_usec,
			p->index,
			prt_names(p->type, v4l2_type_names),
			p->bytesused, p->flags,
			p->field, p->sequence,
			prt_names(p->memory, v4l2_memory_names),
			p->m.userptr, p->length);
	dbgarg2("timecode=%02d:%02d:%02d type=%d, "
		"flags=0x%08d, frames=%d, userbits=0x%08x\n",
			tc->hours, tc->minutes, tc->seconds,
			tc->type, tc->flags, tc->frames, *(__u32 *)tc->userbits);
}