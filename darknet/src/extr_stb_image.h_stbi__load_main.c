#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int bits_per_channel; scalar_t__ num_channels; int /*<<< orphan*/  channel_order; } ;
typedef  TYPE_1__ stbi__result_info ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_ORDER_RGB ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* stbi__bmp_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__bmp_test (int /*<<< orphan*/ *) ; 
 void* stbi__errpuc (char*,char*) ; 
 void* stbi__gif_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__gif_test (int /*<<< orphan*/ *) ; 
 float* stbi__hdr_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__hdr_test (int /*<<< orphan*/ *) ; 
 void* stbi__hdr_to_ldr (float*,int,int,int) ; 
 void* stbi__jpeg_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__jpeg_test (int /*<<< orphan*/ *) ; 
 void* stbi__pic_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__pic_test (int /*<<< orphan*/ *) ; 
 void* stbi__png_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__png_test (int /*<<< orphan*/ *) ; 
 void* stbi__pnm_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__pnm_test (int /*<<< orphan*/ *) ; 
 void* stbi__psd_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*,int) ; 
 scalar_t__ stbi__psd_test (int /*<<< orphan*/ *) ; 
 void* stbi__tga_load (int /*<<< orphan*/ *,int*,int*,int*,int,TYPE_1__*) ; 
 scalar_t__ stbi__tga_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *stbi__load_main(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri, int bpc)
{
   memset(ri, 0, sizeof(*ri)); // make sure it's initialized if we add new fields
   ri->bits_per_channel = 8; // default is 8 so most paths don't have to be changed
   ri->channel_order = STBI_ORDER_RGB; // all current input & output are this, but this is here so we can add BGR order
   ri->num_channels = 0;

   #ifndef STBI_NO_JPEG
   if (stbi__jpeg_test(s)) return stbi__jpeg_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef STBI_NO_PNG
   if (stbi__png_test(s))  return stbi__png_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef STBI_NO_BMP
   if (stbi__bmp_test(s))  return stbi__bmp_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef STBI_NO_GIF
   if (stbi__gif_test(s))  return stbi__gif_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef STBI_NO_PSD
   if (stbi__psd_test(s))  return stbi__psd_load(s,x,y,comp,req_comp, ri, bpc);
   #endif
   #ifndef STBI_NO_PIC
   if (stbi__pic_test(s))  return stbi__pic_load(s,x,y,comp,req_comp, ri);
   #endif
   #ifndef STBI_NO_PNM
   if (stbi__pnm_test(s))  return stbi__pnm_load(s,x,y,comp,req_comp, ri);
   #endif

   #ifndef STBI_NO_HDR
   if (stbi__hdr_test(s)) {
      float *hdr = stbi__hdr_load(s, x,y,comp,req_comp, ri);
      return stbi__hdr_to_ldr(hdr, *x, *y, req_comp ? req_comp : *comp);
   }
   #endif

   #ifndef STBI_NO_TGA
   // test tga last because it's a crappy test!
   if (stbi__tga_test(s))
      return stbi__tga_load(s,x,y,comp,req_comp, ri);
   #endif

   return stbi__errpuc("unknown image type", "Image not of any known type, or corrupt");
}