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
typedef  double emscripten_align4_double ;
typedef  int emscripten_align2_int ;
typedef  double emscripten_align2_float ;
typedef  double emscripten_align2_double ;
typedef  int emscripten_align1_short ;
typedef  int emscripten_align1_int ;
typedef  double emscripten_align1_float ;
typedef  double emscripten_align1_double ;

/* Variables and functions */
 scalar_t__ get_aligned (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main()
{
  emscripten_align4_double *d4 = (emscripten_align4_double*)get_aligned(4);
  *d4 = 17.0;
  printf("addr: %d, value: %f\n", ((int)d4) % 8, *d4);

  emscripten_align2_double *d2 = (emscripten_align2_double*)get_aligned(2);
  *d2 = 18.0;
  printf("addr: %d, value: %f\n", ((int)d2) % 8, *d2);

  emscripten_align1_double *d1 = (emscripten_align1_double*)get_aligned(1);
  *d1 = 19.0;
  printf("addr: %d, value: %f\n", ((int)d1) % 8, *d1);

  emscripten_align2_float *f2 = (emscripten_align2_float*)get_aligned(2);
  *f2 = 20.0;
  printf("addr: %d, value: %f\n", ((int)f2) % 4, *f2);

  emscripten_align1_float *f1 = (emscripten_align1_float*)get_aligned(1);
  *f1 = 21.0;
  printf("addr: %d, value: %f\n", ((int)f1) % 4, *f1);

  emscripten_align2_int *i2 = (emscripten_align2_int*)get_aligned(2);
  *i2 = 22;
  printf("addr: %d, value: %d\n", ((int)i2) % 4, *i2);

  emscripten_align1_int *i1 = (emscripten_align1_int*)get_aligned(1);
  *i1 = 23;
  printf("addr: %d, value: %d\n", ((int)i1) % 4, *i1);

  emscripten_align1_short *s1 = (emscripten_align1_short*)get_aligned(1);
  *s1 = 24;
  printf("addr: %d, value: %d\n", ((int)s1) % 4, (int)*s1);

  return 0;
}