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
struct v4l2_enc_idx {scalar_t__ entries; int entries_cap; int /*<<< orphan*/  reserved; } ;
struct file {int dummy; } ;
struct cx18_stream {int buffers; int bufs_per_mdl; int buf_size; int /*<<< orphan*/  q_free; int /*<<< orphan*/  q_full; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18_mdl {scalar_t__ readpos; scalar_t__ bytesused; } ;
struct cx18_enc_idx_entry {int dummy; } ;
struct cx18 {struct cx18_stream* streams; } ;
typedef  int s32 ;

/* Variables and functions */
 size_t CX18_ENC_STREAM_TYPE_IDX ; 
 int CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN ; 
 int EINVAL ; 
 scalar_t__ V4L2_ENC_IDX_ENTRIES ; 
 struct cx18_mdl* cx18_dequeue (struct cx18_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_enqueue (struct cx18_stream*,struct cx18_mdl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_process_idx_data (struct cx18_stream*,struct cx18_mdl*,struct v4l2_enc_idx*) ; 
 int /*<<< orphan*/  cx18_push (struct cx18_stream*,struct cx18_mdl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_stream_enabled (struct cx18_stream*) ; 
 int /*<<< orphan*/  cx18_stream_load_fw_queue (struct cx18_stream*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cx18_g_enc_index(struct file *file, void *fh,
				struct v4l2_enc_idx *idx)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct cx18_stream *s = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	s32 tmp;
	struct cx18_mdl *mdl;

	if (!cx18_stream_enabled(s)) /* Module options inhibited IDX stream */
		return -EINVAL;

	/* Compute the best case number of entries we can buffer */
	tmp = s->buffers -
			  s->bufs_per_mdl * CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN;
	if (tmp <= 0)
		tmp = 1;
	tmp = tmp * s->buf_size / sizeof(struct cx18_enc_idx_entry);

	/* Fill out the header of the return structure */
	idx->entries = 0;
	idx->entries_cap = tmp;
	memset(idx->reserved, 0, sizeof(idx->reserved));

	/* Pull IDX MDLs and buffers from q_full and populate the entries */
	do {
		mdl = cx18_dequeue(s, &s->q_full);
		if (mdl == NULL) /* No more IDX data right now */
			break;

		/* Extract the Index entry data from the MDL and buffers */
		cx18_process_idx_data(s, mdl, idx);
		if (mdl->readpos < mdl->bytesused) {
			/* We finished with data remaining, push the MDL back */
			cx18_push(s, mdl, &s->q_full);
			break;
		}

		/* We drained this MDL, schedule it to go to the firmware */
		cx18_enqueue(s, mdl, &s->q_free);

	} while (idx->entries < V4L2_ENC_IDX_ENTRIES);

	/* Tell the work handler to send free IDX MDLs to the firmware */
	cx18_stream_load_fw_queue(s);
	return 0;
}