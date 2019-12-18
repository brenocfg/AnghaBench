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
typedef  int /*<<< orphan*/  stbi__result_info ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 float* stbi__errpf (char*,char*) ; 
 int /*<<< orphan*/  stbi__float_postprocess (float*,int*,int*,int*,int) ; 
 float* stbi__hdr_load (int /*<<< orphan*/ *,int*,int*,int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stbi__hdr_test (int /*<<< orphan*/ *) ; 
 float* stbi__ldr_to_hdr (unsigned char*,int,int,int) ; 
 unsigned char* stbi__load_and_postprocess_8bit (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

__attribute__((used)) static float *stbi__loadf_main(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
   unsigned char *data;
   #ifndef STBI_NO_HDR
   if (stbi__hdr_test(s)) {
      stbi__result_info ri;
      float *hdr_data = stbi__hdr_load(s,x,y,comp,req_comp, &ri);
      if (hdr_data)
         stbi__float_postprocess(hdr_data,x,y,comp,req_comp);
      return hdr_data;
   }
   #endif
   data = stbi__load_and_postprocess_8bit(s, x, y, comp, req_comp);
   if (data)
      return stbi__ldr_to_hdr(data, *x, *y, req_comp ? req_comp : *comp);
   return stbi__errpf("unknown image type", "Image not of any known type, or corrupt");
}