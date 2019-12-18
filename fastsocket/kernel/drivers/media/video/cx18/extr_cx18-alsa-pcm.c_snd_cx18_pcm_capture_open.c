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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct cx18* private_data; int /*<<< orphan*/  hw; } ;
struct snd_cx18_card {struct snd_pcm_substream* capture_pcm_substream; struct v4l2_device* v4l2_dev; } ;
struct cx18_stream {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  type; } ;
struct cx18_open_id {int /*<<< orphan*/  type; scalar_t__ open_id; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  pcm_announce_callback; int /*<<< orphan*/  open_id; struct cx18_stream* streams; } ;

/* Variables and functions */
 size_t CX18_ENC_STREAM_TYPE_PCM ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_F_S_STREAMOFF ; 
 int EBUSY ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  cx18_alsa_announce_pcm_data ; 
 scalar_t__ cx18_claim_stream (struct cx18_open_id*,int /*<<< orphan*/ ) ; 
 int cx18_start_v4l2_encode_stream (struct cx18_stream*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cx18_hw_capture ; 
 int /*<<< orphan*/  snd_cx18_lock (struct snd_cx18_card*) ; 
 int /*<<< orphan*/  snd_cx18_unlock (struct snd_cx18_card*) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_cx18_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cx18* to_cx18 (struct v4l2_device*) ; 

__attribute__((used)) static int snd_cx18_pcm_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct v4l2_device *v4l2_dev = cxsc->v4l2_dev;
	struct cx18 *cx = to_cx18(v4l2_dev);
	struct cx18_stream *s;
	struct cx18_open_id item;
	int ret;

	/* Instruct the cx18 to start sending packets */
	snd_cx18_lock(cxsc);
	s = &cx->streams[CX18_ENC_STREAM_TYPE_PCM];

	item.cx = cx;
	item.type = s->type;
	item.open_id = cx->open_id++;

	/* See if the stream is available */
	if (cx18_claim_stream(&item, item.type)) {
		/* No, it's already in use */
		snd_cx18_unlock(cxsc);
		return -EBUSY;
	}

	if (test_bit(CX18_F_S_STREAMOFF, &s->s_flags) ||
	    test_and_set_bit(CX18_F_S_STREAMING, &s->s_flags)) {
		/* We're already streaming.  No additional action required */
		snd_cx18_unlock(cxsc);
		return 0;
	}


	runtime->hw = snd_cx18_hw_capture;
	snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS);
	cxsc->capture_pcm_substream = substream;
	runtime->private_data = cx;

	cx->pcm_announce_callback = cx18_alsa_announce_pcm_data;

	/* Not currently streaming, so start it up */
	set_bit(CX18_F_S_STREAMING, &s->s_flags);
	ret = cx18_start_v4l2_encode_stream(s);
	snd_cx18_unlock(cxsc);

	return 0;
}