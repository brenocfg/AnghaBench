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
struct v4l2_device {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_cx18_card {struct v4l2_device* v4l2_dev; } ;
struct cx18_stream {int /*<<< orphan*/  s_flags; } ;
struct cx18 {int /*<<< orphan*/ * pcm_announce_callback; struct cx18_stream* streams; } ;

/* Variables and functions */
 size_t CX18_ENC_STREAM_TYPE_PCM ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_release_stream (struct cx18_stream*) ; 
 int cx18_stop_v4l2_encode_stream (struct cx18_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cx18_lock (struct snd_cx18_card*) ; 
 int /*<<< orphan*/  snd_cx18_unlock (struct snd_cx18_card*) ; 
 struct snd_cx18_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 struct cx18* to_cx18 (struct v4l2_device*) ; 

__attribute__((used)) static int snd_cx18_pcm_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);
	struct v4l2_device *v4l2_dev = cxsc->v4l2_dev;
	struct cx18 *cx = to_cx18(v4l2_dev);
	struct cx18_stream *s;
	int ret;

	/* Instruct the cx18 to stop sending packets */
	snd_cx18_lock(cxsc);
	s = &cx->streams[CX18_ENC_STREAM_TYPE_PCM];
	ret = cx18_stop_v4l2_encode_stream(s, 0);
	clear_bit(CX18_F_S_STREAMING, &s->s_flags);

	cx18_release_stream(s);

	cx->pcm_announce_callback = NULL;
	snd_cx18_unlock(cxsc);

	return 0;
}