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
struct snd_pcm_sw_params {int period_step; int avail_min; int start_threshold; int stop_threshold; int xfer_align; int boundary; scalar_t__ silence_threshold; scalar_t__ silence_size; int /*<<< orphan*/  tstamp_mode; int /*<<< orphan*/  flags; } ;
struct snd_pcm_hw_params {int period_step; int avail_min; int start_threshold; int stop_threshold; int xfer_align; int boundary; scalar_t__ silence_threshold; scalar_t__ silence_size; int /*<<< orphan*/  tstamp_mode; int /*<<< orphan*/  flags; } ;
struct pcm_config {int channels; int rate; int period_size; int period_count; int start_threshold; int stop_threshold; scalar_t__ silence_threshold; int /*<<< orphan*/  format; } ;
struct pcm {int flags; int noirq_frames_per_msec; int buffer_size; scalar_t__ mmap_buffer; int boundary; int /*<<< orphan*/  fd; struct pcm_config config; } ;
typedef  int /*<<< orphan*/  sparams ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int INT_MAX ; 
 scalar_t__ MAP_FAILED ; 
 int MAP_FILE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  PCM_FORMAT_S16_LE ; 
 int PCM_IN ; 
 int PCM_MMAP ; 
 int PCM_NOIRQ ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  SNDRV_PCM_ACCESS_MMAP_INTERLEAVED ; 
 int /*<<< orphan*/  SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_ACCESS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FRAME_BITS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SUBFORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_HW_PARAMS ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_SW_PARAMS ; 
 int /*<<< orphan*/  SNDRV_PCM_SUBFORMAT_STD ; 
 int /*<<< orphan*/  SNDRV_PCM_TSTAMP_ENABLE ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_sw_params*) ; 
 int /*<<< orphan*/  memset (struct snd_pcm_sw_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* param_get_int (struct snd_pcm_sw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  param_init (struct snd_pcm_sw_params*) ; 
 int /*<<< orphan*/  param_set_int (struct snd_pcm_sw_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  param_set_mask (struct snd_pcm_sw_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  param_set_min (struct snd_pcm_sw_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_format_to_alsa (int /*<<< orphan*/ ) ; 
 int pcm_format_to_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_frames_to_bytes (struct pcm*,int) ; 

__attribute__((used)) static int pcm_set_config(struct pcm *pcm, const struct pcm_config *config)
{
    struct snd_pcm_sw_params sparams;
    struct snd_pcm_hw_params params;

    if (pcm == NULL)
        return -EFAULT;

    if (config)
        pcm->config = *config;
    else
    {
        config = &pcm->config;
        pcm->config.channels = 2;
        pcm->config.rate = 48000;
        pcm->config.period_size = 1024;
        pcm->config.period_count = 4;
        pcm->config.format = PCM_FORMAT_S16_LE;
        pcm->config.start_threshold = config->period_count * config->period_size;
        pcm->config.stop_threshold = config->period_count * config->period_size;
        pcm->config.silence_threshold = 0;
    }

    param_init(&params);
    param_set_mask(&params, SNDRV_PCM_HW_PARAM_FORMAT,
                   pcm_format_to_alsa(config->format));
    param_set_mask(&params, SNDRV_PCM_HW_PARAM_SUBFORMAT,
                   SNDRV_PCM_SUBFORMAT_STD);
    param_set_min(&params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, config->period_size);
    param_set_int(&params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
                  pcm_format_to_bits(config->format));
    param_set_int(&params, SNDRV_PCM_HW_PARAM_FRAME_BITS,
                  pcm_format_to_bits(config->format) * config->channels);
    param_set_int(&params, SNDRV_PCM_HW_PARAM_CHANNELS,
                  config->channels);
    param_set_int(&params, SNDRV_PCM_HW_PARAM_PERIODS, config->period_count);
    param_set_int(&params, SNDRV_PCM_HW_PARAM_RATE, config->rate);

    if (pcm->flags & PCM_NOIRQ)
    {
        if (!(pcm->flags & PCM_MMAP))
        {
            RARCH_ERR("[TINYALSA]: noirq only currently supported with mmap().");
            return -EINVAL;
        }

        params.flags |= SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP;
        pcm->noirq_frames_per_msec = config->rate / 1000;
    }

    if (pcm->flags & PCM_MMAP)
        param_set_mask(&params, SNDRV_PCM_HW_PARAM_ACCESS,
                   SNDRV_PCM_ACCESS_MMAP_INTERLEAVED);
    else
        param_set_mask(&params, SNDRV_PCM_HW_PARAM_ACCESS,
                   SNDRV_PCM_ACCESS_RW_INTERLEAVED);

    if (ioctl(pcm->fd, SNDRV_PCM_IOCTL_HW_PARAMS, &params))
    {
        RARCH_ERR("[TINYALSA]: cannot set HW params.");
        return -errno;
    }

    /* get our refined hw_params */
    pcm->config.period_size = param_get_int(&params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
    pcm->config.period_count = param_get_int(&params, SNDRV_PCM_HW_PARAM_PERIODS);
    pcm->buffer_size = config->period_count * config->period_size;

    if (pcm->flags & PCM_MMAP)
    {
        pcm->mmap_buffer = mmap(NULL, pcm_frames_to_bytes(pcm, pcm->buffer_size),
                                PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, pcm->fd, 0);
        if (pcm->mmap_buffer == MAP_FAILED)
        {
            RARCH_ERR("[TINYALSA]: failed to mmap buffer %d bytes\n",
                 pcm_frames_to_bytes(pcm, pcm->buffer_size));
            return -errno;
        }
    }

    memset(&sparams, 0, sizeof(sparams));
    sparams.tstamp_mode = SNDRV_PCM_TSTAMP_ENABLE;
    sparams.period_step = 1;
    sparams.avail_min   = 1;

    if (!config->start_threshold)
    {
        if (pcm->flags & PCM_IN)
            pcm->config.start_threshold = sparams.start_threshold = 1;
        else
            pcm->config.start_threshold = sparams.start_threshold =
                config->period_count * config->period_size / 2;
    } else
        sparams.start_threshold = config->start_threshold;

    /* pick a high stop threshold - todo: does this need further tuning */
    if (!config->stop_threshold)
    {
        if (pcm->flags & PCM_IN)
            pcm->config.stop_threshold = sparams.stop_threshold =
                config->period_count * config->period_size * 10;
        else
            pcm->config.stop_threshold = sparams.stop_threshold =
                config->period_count * config->period_size;
    }
    else
        sparams.stop_threshold = config->stop_threshold;

    sparams.xfer_align = config->period_size / 2; /* needed for old kernels */
    sparams.silence_size = 0;
    sparams.silence_threshold = config->silence_threshold;
    pcm->boundary = sparams.boundary = pcm->buffer_size;

    while (pcm->boundary * 2 <= INT_MAX - pcm->buffer_size)
        pcm->boundary *= 2;

    if (ioctl(pcm->fd, SNDRV_PCM_IOCTL_SW_PARAMS, &sparams))
    {
        RARCH_ERR("[TINYALSA]: Cannot set HW params.\n");
        return -errno;
    }

    return 0;
}