#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvr2_stream {int dummy; } ;
struct pvr2_buffer {unsigned int id; int /*<<< orphan*/  purb; int /*<<< orphan*/  list_overhead; int /*<<< orphan*/  state; struct pvr2_stream* stream; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PVR2_TRACE_BUF_POOL ; 
 int /*<<< orphan*/  memset (struct pvr2_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvr2_buffer_describe (struct pvr2_buffer*,char*) ; 
 int /*<<< orphan*/  pvr2_buffer_state_none ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_buffer*,struct pvr2_stream*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_buffer_init(struct pvr2_buffer *bp,
			    struct pvr2_stream *sp,
			    unsigned int id)
{
	memset(bp,0,sizeof(*bp));
	bp->signature = BUFFER_SIG;
	bp->id = id;
	pvr2_trace(PVR2_TRACE_BUF_POOL,
		   "/*---TRACE_FLOW---*/ bufferInit     %p stream=%p",bp,sp);
	bp->stream = sp;
	bp->state = pvr2_buffer_state_none;
	INIT_LIST_HEAD(&bp->list_overhead);
	bp->purb = usb_alloc_urb(0,GFP_KERNEL);
	if (! bp->purb) return -ENOMEM;
#ifdef SANITY_CHECK_BUFFERS
	pvr2_buffer_describe(bp,"create");
#endif
	return 0;
}