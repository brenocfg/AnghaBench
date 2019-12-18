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
struct cx18_stream {int type; int mdl_size; int bufs_per_mdl; int buf_size; TYPE_2__* cx; } ;
struct TYPE_3__ {int height; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_60hz; TYPE_1__ params; } ;

/* Variables and functions */
#define  CX18_ENC_STREAM_TYPE_VBI 129 
#define  CX18_ENC_STREAM_TYPE_YUV 128 
 int /*<<< orphan*/  cx18_load_queues (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_raw_vbi (TYPE_2__*) ; 
 int /*<<< orphan*/  cx18_unload_queues (struct cx18_stream*) ; 
 int vbi_active_samples ; 
 int vbi_hblank_samples_50Hz ; 
 int vbi_hblank_samples_60Hz ; 

__attribute__((used)) static void cx18_stream_configure_mdls(struct cx18_stream *s)
{
	cx18_unload_queues(s);

	switch (s->type) {
	case CX18_ENC_STREAM_TYPE_YUV:
		/*
		 * Height should be a multiple of 32 lines.
		 * Set the MDL size to the exact size needed for one frame.
		 * Use enough buffers per MDL to cover the MDL size
		 */
		s->mdl_size = 720 * s->cx->params.height * 3 / 2;
		s->bufs_per_mdl = s->mdl_size / s->buf_size;
		if (s->mdl_size % s->buf_size)
			s->bufs_per_mdl++;
		break;
	case CX18_ENC_STREAM_TYPE_VBI:
		s->bufs_per_mdl = 1;
		if  (cx18_raw_vbi(s->cx)) {
			s->mdl_size = (s->cx->is_60hz ? 12 : 18)
						       * 2 * vbi_active_samples;
		} else {
			/*
			 * See comment in cx18_vbi_setup() below about the
			 * extra lines we capture in sliced VBI mode due to
			 * the lines on which EAV RP codes toggle.
			*/
			s->mdl_size = s->cx->is_60hz
				   ? (21 - 4 + 1) * 2 * vbi_hblank_samples_60Hz
				   : (23 - 2 + 1) * 2 * vbi_hblank_samples_50Hz;
		}
		break;
	default:
		s->bufs_per_mdl = 1;
		s->mdl_size = s->buf_size * s->bufs_per_mdl;
		break;
	}

	cx18_load_queues(s);
}