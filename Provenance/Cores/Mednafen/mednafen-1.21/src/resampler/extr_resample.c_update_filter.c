#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* spx_word16_t ;
typedef  size_t spx_uint32_t ;
typedef  size_t spx_int32_t ;
struct TYPE_5__ {int oversample; size_t base_length; int downsample_bandwidth; int upsample_bandwidth; int /*<<< orphan*/  window_func; } ;
struct TYPE_4__ {size_t filt_len; int oversample; size_t quality; int num_rate; int den_rate; int cutoff; int sinc_table_length; int int_advance; int frac_advance; int mem_alloc_size; int buffer_size; int nb_channels; int* magic_samples; size_t* last_sample; void** mem; int /*<<< orphan*/  started; void* resampler_ptr; void** sinc_table; } ;
typedef  TYPE_1__ SpeexResamplerState ;

/* Variables and functions */
 TYPE_3__* quality_map ; 
 void* resampler_basic_direct_double ; 
 void* resampler_basic_direct_single ; 
 void* resampler_basic_interpolate_double ; 
 void* resampler_basic_interpolate_single ; 
 void* sinc (int,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ speex_alloc (int) ; 
 scalar_t__ speex_realloc (void**,int) ; 

__attribute__((used)) static void update_filter(SpeexResamplerState *st)
{
   spx_uint32_t old_length;
   
   old_length = st->filt_len;
   st->oversample = quality_map[st->quality].oversample;
   st->filt_len = quality_map[st->quality].base_length;
   
   if (st->num_rate > st->den_rate)
   {
      /* down-sampling */
      st->cutoff = quality_map[st->quality].downsample_bandwidth * st->den_rate / st->num_rate;
      /* FIXME: divide the numerator and denominator by a certain amount if they're too large */
      st->filt_len = st->filt_len*st->num_rate / st->den_rate;
      /* Round down to make sure we have a multiple of 4 */
      st->filt_len &= (~0x3);
      if (2*st->den_rate < st->num_rate)
         st->oversample >>= 1;
      if (4*st->den_rate < st->num_rate)
         st->oversample >>= 1;
      if (8*st->den_rate < st->num_rate)
         st->oversample >>= 1;
      if (16*st->den_rate < st->num_rate)
         st->oversample >>= 1;
      if (st->oversample < 1)
         st->oversample = 1;
   } else {
      /* up-sampling */
      st->cutoff = quality_map[st->quality].upsample_bandwidth;
   }
   
   /* Choose the resampling type that requires the least amount of memory */
   if (st->den_rate <= st->oversample)
   {
      spx_uint32_t i;
      if (!st->sinc_table)
         st->sinc_table = (spx_word16_t *)speex_alloc(st->filt_len*st->den_rate*sizeof(spx_word16_t));
      else if (st->sinc_table_length < st->filt_len*st->den_rate)
      {
         st->sinc_table = (spx_word16_t *)speex_realloc(st->sinc_table,st->filt_len*st->den_rate*sizeof(spx_word16_t));
         st->sinc_table_length = st->filt_len*st->den_rate;
      }
      for (i=0;i<st->den_rate;i++)
      {
         spx_int32_t j;
         for (j=0;j<st->filt_len;j++)
         {
            st->sinc_table[i*st->filt_len+j] = sinc(st->cutoff,((j-(spx_int32_t)st->filt_len/2+1)-((float)i)/st->den_rate), st->filt_len, quality_map[st->quality].window_func);
         }
      }
#ifdef FIXED_POINT
      st->resampler_ptr = resampler_basic_direct_single;
#else
      if (st->quality>8)
         st->resampler_ptr = resampler_basic_direct_double;
      else
         st->resampler_ptr = resampler_basic_direct_single;
#endif
      /*fprintf (stderr, "resampler uses direct sinc table and normalised cutoff %f\n", cutoff);*/
   } else {
      spx_int32_t i;
      if (!st->sinc_table)
         st->sinc_table = (spx_word16_t *)speex_alloc((st->filt_len*st->oversample+8)*sizeof(spx_word16_t));
      else if (st->sinc_table_length < st->filt_len*st->oversample+8)
      {
         st->sinc_table = (spx_word16_t *)speex_realloc(st->sinc_table,(st->filt_len*st->oversample+8)*sizeof(spx_word16_t));
         st->sinc_table_length = st->filt_len*st->oversample+8;
      }
      for (i=-4;i<(spx_int32_t)(st->oversample*st->filt_len+4);i++)
         st->sinc_table[i+4] = sinc(st->cutoff,(i/(float)st->oversample - st->filt_len/2), st->filt_len, quality_map[st->quality].window_func);
#ifdef FIXED_POINT
      st->resampler_ptr = resampler_basic_interpolate_single;
#else
      if (st->quality>8)
         st->resampler_ptr = resampler_basic_interpolate_double;
      else
         st->resampler_ptr = resampler_basic_interpolate_single;
#endif
      /*fprintf (stderr, "resampler uses interpolated sinc table and normalised cutoff %f\n", cutoff);*/
   }
   st->int_advance = st->num_rate/st->den_rate;
   st->frac_advance = st->num_rate%st->den_rate;

   
   /* Here's the place where we update the filter memory to take into account
      the change in filter length. It's probably the messiest part of the code
      due to handling of lots of corner cases. */
   if (!st->mem)
   {
      spx_uint32_t i;
      st->mem_alloc_size = st->filt_len-1 + st->buffer_size;
      st->mem = (spx_word16_t*)speex_alloc(st->nb_channels*st->mem_alloc_size * sizeof(spx_word16_t));
      for (i=0;i<st->nb_channels*st->mem_alloc_size;i++)
         st->mem[i] = 0;
      /*speex_warning("init filter");*/
   } else if (!st->started)
   {
      spx_uint32_t i;
      st->mem_alloc_size = st->filt_len-1 + st->buffer_size;
      st->mem = (spx_word16_t*)speex_realloc(st->mem, st->nb_channels*st->mem_alloc_size * sizeof(spx_word16_t));
      for (i=0;i<st->nb_channels*st->mem_alloc_size;i++)
         st->mem[i] = 0;
      /*speex_warning("reinit filter");*/
   } else if (st->filt_len > old_length)
   {
      spx_int32_t i;
      /* Increase the filter length */
      /*speex_warning("increase filter size");*/
      int old_alloc_size = st->mem_alloc_size;
      if ((st->filt_len-1 + st->buffer_size) > st->mem_alloc_size)
      {
         st->mem_alloc_size = st->filt_len-1 + st->buffer_size;
         st->mem = (spx_word16_t*)speex_realloc(st->mem, st->nb_channels*st->mem_alloc_size * sizeof(spx_word16_t));
      }
      for (i=st->nb_channels-1;i>=0;i--)
      {
         spx_int32_t j;
         spx_uint32_t olen = old_length;
         /*if (st->magic_samples[i])*/
         {
            /* Try and remove the magic samples as if nothing had happened */
            
            /* FIXME: This is wrong but for now we need it to avoid going over the array bounds */
            olen = old_length + 2*st->magic_samples[i];
            for (j=old_length-2+st->magic_samples[i];j>=0;j--)
               st->mem[i*st->mem_alloc_size+j+st->magic_samples[i]] = st->mem[i*old_alloc_size+j];
            for (j=0;j<st->magic_samples[i];j++)
               st->mem[i*st->mem_alloc_size+j] = 0;
            st->magic_samples[i] = 0;
         }
         if (st->filt_len > olen)
         {
            /* If the new filter length is still bigger than the "augmented" length */
            /* Copy data going backward */
            for (j=0;j<olen-1;j++)
               st->mem[i*st->mem_alloc_size+(st->filt_len-2-j)] = st->mem[i*st->mem_alloc_size+(olen-2-j)];
            /* Then put zeros for lack of anything better */
            for (;j<st->filt_len-1;j++)
               st->mem[i*st->mem_alloc_size+(st->filt_len-2-j)] = 0;
            /* Adjust last_sample */
            st->last_sample[i] += (st->filt_len - olen)/2;
         } else {
            /* Put back some of the magic! */
            st->magic_samples[i] = (olen - st->filt_len)/2;
            for (j=0;j<st->filt_len-1+st->magic_samples[i];j++)
               st->mem[i*st->mem_alloc_size+j] = st->mem[i*st->mem_alloc_size+j+st->magic_samples[i]];
         }
      }
   } else if (st->filt_len < old_length)
   {
      spx_uint32_t i;
      /* Reduce filter length, this a bit tricky. We need to store some of the memory as "magic"
         samples so they can be used directly as input the next time(s) */
      for (i=0;i<st->nb_channels;i++)
      {
         spx_uint32_t j;
         spx_uint32_t old_magic = st->magic_samples[i];
         st->magic_samples[i] = (old_length - st->filt_len)/2;
         /* We must copy some of the memory that's no longer used */
         /* Copy data going backward */
         for (j=0;j<st->filt_len-1+st->magic_samples[i]+old_magic;j++)
            st->mem[i*st->mem_alloc_size+j] = st->mem[i*st->mem_alloc_size+j+st->magic_samples[i]];
         st->magic_samples[i] += old_magic;
      }
   }

}