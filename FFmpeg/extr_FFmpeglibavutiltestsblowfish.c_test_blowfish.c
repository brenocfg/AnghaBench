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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  AVBlowfish ;

/* Variables and functions */
 int /*<<< orphan*/  av_blowfish_crypt (int /*<<< orphan*/ *,int*,int const*,int,int*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_blowfish(AVBlowfish *ctx, uint8_t *dst, const uint8_t *src,
                          const uint8_t *ref, int len, uint8_t *iv, int dir,
                          const char *test)
{
    av_blowfish_crypt(ctx, dst, src, len, iv, dir);
    if (memcmp(dst, ref, 8*len)) {
        int i;
        printf("%s failed\ngot      ", test);
        for (i = 0; i < 8*len; i++)
            printf("%02x ", dst[i]);
        printf("\nexpected ");
        for (i = 0; i < 8*len; i++)
            printf("%02x ", ref[i]);
        printf("\n");
        exit(1);
    }
}