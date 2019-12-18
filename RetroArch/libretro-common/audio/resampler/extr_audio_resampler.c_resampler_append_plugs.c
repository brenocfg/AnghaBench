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
struct TYPE_3__ {void* (* init ) (int /*<<< orphan*/ *,double,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ retro_resampler_t ;
typedef  int /*<<< orphan*/  resampler_simd_mask_t ;
typedef  enum resampler_quality { ____Placeholder_resampler_quality } resampler_quality ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_features_get () ; 
 int /*<<< orphan*/  resampler_config ; 
 void* stub1 (int /*<<< orphan*/ *,double,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool resampler_append_plugs(void **re,
      const retro_resampler_t **backend,
      enum resampler_quality quality,
      double bw_ratio)
{
   resampler_simd_mask_t mask = (resampler_simd_mask_t)cpu_features_get();

   if (*backend)
      *re = (*backend)->init(&resampler_config, bw_ratio, quality, mask);

   if (!*re)
      return false;
   return true;
}