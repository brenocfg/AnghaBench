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

/* Variables and functions */
#define  RESAMPLER_ERR_ALLOC_FAILED 132 
#define  RESAMPLER_ERR_BAD_STATE 131 
#define  RESAMPLER_ERR_INVALID_ARG 130 
#define  RESAMPLER_ERR_PTR_OVERLAP 129 
#define  RESAMPLER_ERR_SUCCESS 128 

const char *speex_resampler_strerror(int err)
{
   switch (err)
   {
      case RESAMPLER_ERR_SUCCESS:
         return "Success.";
      case RESAMPLER_ERR_ALLOC_FAILED:
         return "Memory allocation failed.";
      case RESAMPLER_ERR_BAD_STATE:
         return "Bad resampler state.";
      case RESAMPLER_ERR_INVALID_ARG:
         return "Invalid argument.";
      case RESAMPLER_ERR_PTR_OVERLAP:
         return "Input and output buffers overlap.";
      default:
         return "Unknown error. Bad error code or strange version mismatch.";
   }
}