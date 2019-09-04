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
typedef  void stbi_uc ;
typedef  int /*<<< orphan*/  stbi__result_info ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_FREE (void*) ; 
 int /*<<< orphan*/  STBI_NOTUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 scalar_t__ stbi__at_eof (int /*<<< orphan*/ *) ; 
 void* stbi__convert_format (void*,int,int,int,int) ; 
 void* stbi__errpuc (char*,char*) ; 
 int stbi__get16be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__get32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__mad3sizes_valid (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stbi__malloc_mad3 (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbi__pic_load_core (int /*<<< orphan*/ *,int,int,int*,void*) ; 

__attribute__((used)) static void *stbi__pic_load(stbi__context *s,int *px,int *py,int *comp,int req_comp, stbi__result_info *ri)
{
   stbi_uc *result;
   int i, x,y, internal_comp;
   STBI_NOTUSED(ri);

   if (!comp) comp = &internal_comp;

   for (i=0; i<92; ++i)
      stbi__get8(s);

   x = stbi__get16be(s);
   y = stbi__get16be(s);
   if (stbi__at_eof(s))  return stbi__errpuc("bad file","file too short (pic header)");
   if (!stbi__mad3sizes_valid(x, y, 4, 0)) return stbi__errpuc("too large", "PIC image too large to decode");

   stbi__get32be(s); //skip `ratio'
   stbi__get16be(s); //skip `fields'
   stbi__get16be(s); //skip `pad'

   // intermediate buffer is RGBA
   result = (stbi_uc *) stbi__malloc_mad3(x, y, 4, 0);
   memset(result, 0xff, x*y*4);

   if (!stbi__pic_load_core(s,x,y,comp, result)) {
      STBI_FREE(result);
      result=0;
   }
   *px = x;
   *py = y;
   if (req_comp == 0) req_comp = *comp;
   result=stbi__convert_format(result,4,req_comp,x,y);

   return result;
}