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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int (* me_cmp_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ;
typedef  double int64_t ;

/* Variables and functions */
 int HEIGHT ; 
 int NB_ITS ; 
 int WIDTH ; 
 double av_gettime_relative () ; 
 int dummy ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  fill_random (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * img1 ; 
 int /*<<< orphan*/ * img2 ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_motion(const char *name,
                 me_cmp_func test_func, me_cmp_func ref_func)
{
    int x, y, d1, d2, it;
    uint8_t *ptr;
    int64_t ti;
    printf("testing '%s'\n", name);

    /* test correctness */
    for(it=0;it<20;it++) {

        fill_random(img1, WIDTH * HEIGHT);
        fill_random(img2, WIDTH * HEIGHT);

        for(y=0;y<HEIGHT-17;y++) {
            for(x=0;x<WIDTH-17;x++) {
                ptr = img2 + y * WIDTH + x;
                d1 = test_func(NULL, img1, ptr, WIDTH, 8);
                d2 = ref_func(NULL, img1, ptr, WIDTH, 8);
                if (d1 != d2) {
                    printf("error: mmx=%d c=%d\n", d1, d2);
                }
            }
        }
    }
    emms_c();

    /* speed test */
    ti = av_gettime_relative();
    d1 = 0;
    for(it=0;it<NB_ITS;it++) {
        for(y=0;y<HEIGHT-17;y++) {
            for(x=0;x<WIDTH-17;x++) {
                ptr = img2 + y * WIDTH + x;
                d1 += test_func(NULL, img1, ptr, WIDTH, 8);
            }
        }
    }
    emms_c();
    dummy = d1; /* avoid optimization */
    ti = av_gettime_relative() - ti;

    printf("  %0.0f kop/s\n",
           (double)NB_ITS * (WIDTH - 16) * (HEIGHT - 16) /
           (double)(ti / 1000.0));
}