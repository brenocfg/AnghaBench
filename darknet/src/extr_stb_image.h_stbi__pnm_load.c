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
typedef  void stbi_uc ;
typedef  int /*<<< orphan*/  stbi__result_info ;
struct TYPE_5__ {int img_x; int img_y; int img_n; } ;
typedef  TYPE_1__ stbi__context ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_NOTUSED (int /*<<< orphan*/ *) ; 
 void* stbi__convert_format (void*,int,int,int,int) ; 
 void* stbi__errpuc (char*,char*) ; 
 int /*<<< orphan*/  stbi__getn (TYPE_1__*,void*,int) ; 
 int /*<<< orphan*/  stbi__mad3sizes_valid (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stbi__malloc_mad3 (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbi__pnm_info (TYPE_1__*,int*,int*,int*) ; 

__attribute__((used)) static void *stbi__pnm_load(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri)
{
   stbi_uc *out;
   STBI_NOTUSED(ri);

   if (!stbi__pnm_info(s, (int *)&s->img_x, (int *)&s->img_y, (int *)&s->img_n))
      return 0;

   *x = s->img_x;
   *y = s->img_y;
   if (comp) *comp = s->img_n;

   if (!stbi__mad3sizes_valid(s->img_n, s->img_x, s->img_y, 0))
      return stbi__errpuc("too large", "PNM too large");

   out = (stbi_uc *) stbi__malloc_mad3(s->img_n, s->img_x, s->img_y, 0);
   if (!out) return stbi__errpuc("outofmem", "Out of memory");
   stbi__getn(s, out, s->img_n * s->img_x * s->img_y);

   if (req_comp && req_comp != s->img_n) {
      out = stbi__convert_format(out, s->img_n, req_comp, s->img_x, s->img_y);
      if (out == NULL) return out; // stbi__convert_format frees input on failure
   }
   return out;
}