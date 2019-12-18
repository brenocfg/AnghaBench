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
struct resampler_config {int dummy; } ;
typedef  int /*<<< orphan*/  resampler_simd_mask_t ;
typedef  enum resampler_quality { ____Placeholder_resampler_quality } resampler_quality ;

/* Variables and functions */

__attribute__((used)) static void *resampler_null_init(const struct resampler_config *config,
      double bandwidth_mod,
      enum resampler_quality quality,
      resampler_simd_mask_t mask)
{
   return (void*)0;
}