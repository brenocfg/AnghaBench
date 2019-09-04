#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* custom_deflate ) (unsigned char**,size_t*,unsigned char const*,size_t,TYPE_1__ const*) ;} ;
typedef  TYPE_1__ LodePNGCompressSettings ;

/* Variables and functions */
 int lodepng_deflate (unsigned char**,size_t*,unsigned char const*,size_t,TYPE_1__ const*) ; 
 int stub1 (unsigned char**,size_t*,unsigned char const*,size_t,TYPE_1__ const*) ; 

__attribute__((used)) static unsigned deflate(unsigned char** out, size_t* outsize,
                        const unsigned char* in, size_t insize,
                        const LodePNGCompressSettings* settings)
{
  if(settings->custom_deflate)
  {
    return settings->custom_deflate(out, outsize, in, insize, settings);
  }
  else
  {
    return lodepng_deflate(out, outsize, in, insize, settings);
  }
}