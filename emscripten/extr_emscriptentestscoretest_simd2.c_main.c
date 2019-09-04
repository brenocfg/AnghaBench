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
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_add_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set_ps (double,double,double,double) ; 
 int /*<<< orphan*/  _mm_store_ps (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,float) ; 

int main(int argc, char **argv) {
  float __attribute__((__aligned__(16))) ar[4];
  __m128 v1 = _mm_set_ps(9.0, 4.0, 0, -9.0);
  __m128 v2 = _mm_set_ps(7.0, 3.0, 2.5, 1.0);
  __m128 v3 = _mm_add_ps(v1, v2);
  _mm_store_ps(ar, v3);

  for (int i = 0; i < 4; i++) {
    printf("%f\n", ar[i]);
  }

  return 0;
}