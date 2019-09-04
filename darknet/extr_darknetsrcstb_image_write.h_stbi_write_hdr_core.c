#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,char*,int) ;} ;
typedef  TYPE_1__ stbi__write_context ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  STBIW_FREE (unsigned char*) ; 
 scalar_t__ STBIW_MALLOC (int) ; 
 int sprintf (char*,char*,int,int) ; 
 scalar_t__ stbi__flip_vertically_on_write ; 
 int /*<<< orphan*/  stbiw__write_hdr_scanline (TYPE_1__*,int,int,unsigned char*,float*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int stbi_write_hdr_core(stbi__write_context *s, int x, int y, int comp, float *data)
{
   if (y <= 0 || x <= 0 || data == NULL)
      return 0;
   else {
      // Each component is stored separately. Allocate scratch space for full output scanline.
      unsigned char *scratch = (unsigned char *) STBIW_MALLOC(x*4);
      int i, len;
      char buffer[128];
      char header[] = "#?RADIANCE\n# Written by stb_image_write.h\nFORMAT=32-bit_rle_rgbe\n";
      s->func(s->context, header, sizeof(header)-1);

#ifdef STBI_MSC_SECURE_CRT
      len = sprintf_s(buffer, "EXPOSURE=          1.0000000000000\n\n-Y %d +X %d\n", y, x);
#else
      len = sprintf(buffer, "EXPOSURE=          1.0000000000000\n\n-Y %d +X %d\n", y, x);
#endif
      s->func(s->context, buffer, len);

      for(i=0; i < y; i++)
         stbiw__write_hdr_scanline(s, x, comp, scratch, data + comp*x*(stbi__flip_vertically_on_write ? y-1-i : i)*x);
      STBIW_FREE(scratch);
      return 1;
   }
}