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
typedef  void stbi_uc ;
struct TYPE_4__ {int w; int h; int delay; int /*<<< orphan*/  background; int /*<<< orphan*/  history; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ stbi__gif ;
typedef  int /*<<< orphan*/  stbi__context ;
typedef  int /*<<< orphan*/  g ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_FREE (int /*<<< orphan*/ ) ; 
 scalar_t__ STBI_REALLOC (int*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* stbi__convert_format (void*,int,int,int,int) ; 
 void* stbi__errpuc (char*,char*) ; 
 void* stbi__gif_load_next (int /*<<< orphan*/ *,TYPE_1__*,int*,int,void*) ; 
 scalar_t__ stbi__gif_test (int /*<<< orphan*/ *) ; 
 scalar_t__ stbi__malloc (int) ; 

__attribute__((used)) static void *stbi__load_gif_main(stbi__context *s, int **delays, int *x, int *y, int *z, int *comp, int req_comp)
{
   if (stbi__gif_test(s)) {
      int layers = 0; 
      stbi_uc *u = 0;
      stbi_uc *out = 0;
      stbi_uc *two_back = 0; 
      stbi__gif g;
      int stride; 
      memset(&g, 0, sizeof(g));
      if (delays) {
         *delays = 0; 
      }

      do {
         u = stbi__gif_load_next(s, &g, comp, req_comp, two_back);
         if (u == (stbi_uc *) s) u = 0;  // end of animated gif marker

         if (u) {
            *x = g.w;
            *y = g.h;
            ++layers; 
            stride = g.w * g.h * 4; 
         
            if (out) {
               out = (stbi_uc*) STBI_REALLOC( out, layers * stride ); 
               if (delays) {
                  *delays = (int*) STBI_REALLOC( *delays, sizeof(int) * layers ); 
               }
            } else {
               out = (stbi_uc*)stbi__malloc( layers * stride ); 
               if (delays) {
                  *delays = (int*) stbi__malloc( layers * sizeof(int) ); 
               }
            }
            memcpy( out + ((layers - 1) * stride), u, stride ); 
            if (layers >= 2) {
               two_back = out - 2 * stride; 
            }

            if (delays) {
               (*delays)[layers - 1U] = g.delay; 
            }
         }
      } while (u != 0); 

      // free temp buffer; 
      STBI_FREE(g.out); 
      STBI_FREE(g.history); 
      STBI_FREE(g.background); 

      // do the final conversion after loading everything; 
      if (req_comp && req_comp != 4)
         out = stbi__convert_format(out, 4, req_comp, layers * g.w, g.h);

      *z = layers; 
      return out;
   } else {
      return stbi__errpuc("not GIF", "Image was not as a gif type."); 
   }
}