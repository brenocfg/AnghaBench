#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbi__uint16 ;
struct TYPE_8__ {int bits_per_channel; } ;
typedef  TYPE_2__ stbi__result_info ;
struct TYPE_9__ {int depth; int /*<<< orphan*/ * idata; int /*<<< orphan*/ * expanded; int /*<<< orphan*/ * out; TYPE_1__* s; } ;
typedef  TYPE_3__ stbi__png ;
struct TYPE_7__ {int img_out_n; int img_x; int img_y; int img_n; } ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STBI__SCAN_load ; 
 void* stbi__convert_format (unsigned char*,int,int,int,int) ; 
 void* stbi__convert_format16 (int /*<<< orphan*/ *,int,int,int,int) ; 
 void* stbi__errpuc (char*,char*) ; 
 scalar_t__ stbi__parse_png_file (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *stbi__do_png(stbi__png *p, int *x, int *y, int *n, int req_comp, stbi__result_info *ri)
{
   void *result=NULL;
   if (req_comp < 0 || req_comp > 4) return stbi__errpuc("bad req_comp", "Internal error");
   if (stbi__parse_png_file(p, STBI__SCAN_load, req_comp)) {
      if (p->depth < 8)
         ri->bits_per_channel = 8;
      else
         ri->bits_per_channel = p->depth;
      result = p->out;
      p->out = NULL;
      if (req_comp && req_comp != p->s->img_out_n) {
         if (ri->bits_per_channel == 8)
            result = stbi__convert_format((unsigned char *) result, p->s->img_out_n, req_comp, p->s->img_x, p->s->img_y);
         else
            result = stbi__convert_format16((stbi__uint16 *) result, p->s->img_out_n, req_comp, p->s->img_x, p->s->img_y);
         p->s->img_out_n = req_comp;
         if (result == NULL) return result;
      }
      *x = p->s->img_x;
      *y = p->s->img_y;
      if (n) *n = p->s->img_n;
   }
   STBI_FREE(p->out);      p->out      = NULL;
   STBI_FREE(p->expanded); p->expanded = NULL;
   STBI_FREE(p->idata);    p->idata    = NULL;

   return result;
}