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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  format; int /*<<< orphan*/  rate; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ buf; int /*<<< orphan*/  addr; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  stereo; int /*<<< orphan*/  format; int /*<<< orphan*/  rate; scalar_t__ capturing; scalar_t__ playing; } ;
struct snd_harmony {TYPE_2__ cbuf; TYPE_1__ st; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HARMONY_SS_MONO ; 
 int /*<<< orphan*/  HARMONY_SS_STEREO ; 
 int /*<<< orphan*/  harmony_set_control (struct snd_harmony*) ; 
 int /*<<< orphan*/  snd_harmony_rate_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_harmony_set_data_format (struct snd_harmony*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_harmony* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_harmony_capture_prepare(struct snd_pcm_substream *ss)
{
        struct snd_harmony *h = snd_pcm_substream_chip(ss);
        struct snd_pcm_runtime *rt = ss->runtime;

	if (h->st.playing)
		return -EBUSY;

        h->cbuf.size = snd_pcm_lib_buffer_bytes(ss);
        h->cbuf.count = snd_pcm_lib_period_bytes(ss);
	if (h->cbuf.buf >= h->cbuf.size)
	        h->cbuf.buf = 0;
	h->st.capturing = 0;

        h->st.rate = snd_harmony_rate_bits(rt->rate);
        h->st.format = snd_harmony_set_data_format(h, rt->format, 0);

        if (rt->channels == 2)
                h->st.stereo = HARMONY_SS_STEREO;
        else
                h->st.stereo = HARMONY_SS_MONO;

        harmony_set_control(h);

        h->cbuf.addr = rt->dma_addr;

        return 0;
}