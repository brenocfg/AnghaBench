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
typedef  int spx_uint32_t ;
typedef  int /*<<< orphan*/  spx_int16_t ;
struct TYPE_3__ {unsigned char* data_in; int input_frames; float src_ratio; unsigned char* data_out; int output_frames; int input_frames_used; scalar_t__ end_of_input; } ;

/* Variables and functions */
 scalar_t__ RESAMPLER_SPEEX ; 
 scalar_t__ RESAMPLER_SRC ; 
 scalar_t__ Resample ; 
 int /*<<< orphan*/  ResampleQuality ; 
 unsigned char* _dest ; 
 int _dest_len ; 
 unsigned char* _src ; 
 int _src_len ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * speex_resampler_init (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speex_resampler_process_interleaved_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  speex_resampler_set_rate (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * spx_state ; 
 TYPE_1__ src_data ; 
 int /*<<< orphan*/  src_float_to_short_array (unsigned char*,short*,int) ; 
 int /*<<< orphan*/ * src_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  src_process (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  src_short_to_float_array (short*,unsigned char*,int) ; 
 int /*<<< orphan*/ * src_state ; 

__attribute__((used)) static int resample(unsigned char *input, int input_avail, int oldsamplerate, unsigned char *output, int output_needed, int newsamplerate)
{
    int *psrc = (int*)input;
    int *pdest = (int*)output;
    int i = 0, j = 0;

#ifdef USE_SPEEX
    spx_uint32_t in_len, out_len;
    if(Resample == RESAMPLER_SPEEX)
    {
        if(spx_state == NULL)
        {
            spx_state = speex_resampler_init(2, oldsamplerate, newsamplerate, ResampleQuality,  &error);
            if(spx_state == NULL)
            {
                memset(output, 0, output_needed);
                return 0;
            }
        }
        speex_resampler_set_rate(spx_state, oldsamplerate, newsamplerate);
        in_len = input_avail / 4;
        out_len = output_needed / 4;

        if ((error = speex_resampler_process_interleaved_int(spx_state, (const spx_int16_t *)input, &in_len, (spx_int16_t *)output, &out_len)))
        {
            memset(output, 0, output_needed);
            return input_avail;  // number of bytes consumed
        }
        return in_len * 4;
    }
#endif
#ifdef USE_SRC
    if(Resample == RESAMPLER_SRC)
    {
        // the high quality resampler needs more input than the samplerate ratio would indicate to work properly
        if (input_avail > output_needed * 3 / 2)
            input_avail = output_needed * 3 / 2; // just to avoid too much short-float-short conversion time
        if (_src_len < input_avail*2 && input_avail > 0)
        {
            if(_src) free(_src);
            _src_len = input_avail*2;
            _src = malloc(_src_len);
        }
        if (_dest_len < output_needed*2 && output_needed > 0)
        {
            if(_dest) free(_dest);
            _dest_len = output_needed*2;
            _dest = malloc(_dest_len);
        }
        memset(_src,0,_src_len);
        memset(_dest,0,_dest_len);
        if(src_state == NULL)
        {
            src_state = src_new (ResampleQuality, 2, &error);
            if(src_state == NULL)
            {
                memset(output, 0, output_needed);
                return 0;
            }
        }
        src_short_to_float_array ((short *) input, _src, input_avail/2);
        src_data.end_of_input = 0;
        src_data.data_in = _src;
        src_data.input_frames = input_avail/4;
        src_data.src_ratio = (float) newsamplerate / oldsamplerate;
        src_data.data_out = _dest;
        src_data.output_frames = output_needed/4;
        if ((error = src_process (src_state, &src_data)))
        {
            memset(output, 0, output_needed);
            return input_avail;  // number of bytes consumed
        }
        src_float_to_short_array (_dest, (short *) output, output_needed/2);
        return src_data.input_frames_used * 4;
    }
#endif
    // RESAMPLE == TRIVIAL
    if (newsamplerate >= oldsamplerate)
    {
        int sldf = oldsamplerate;
        int const2 = 2*sldf;
        int dldf = newsamplerate;
        int const1 = const2 - 2*dldf;
        int criteria = const2 - dldf;
        for (i = 0; i < output_needed/4; i++)
        {
            pdest[i] = psrc[j];
            if(criteria >= 0)
            {
                ++j;
                criteria += const1;
            }
            else criteria += const2;
        }
        return j * 4; //number of bytes consumed
    }
    // newsamplerate < oldsamplerate, this only happens when speed_factor > 1
    for (i = 0; i < output_needed/4; i++)
    {
        j = i * oldsamplerate / newsamplerate;
        pdest[i] = psrc[j];
    }
    return j * 4; //number of bytes consumed
}