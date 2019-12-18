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
typedef  char const uint8_t ;
struct AVTEA {int dummy; } ;

/* Variables and functions */
 int TEA_NUM_TESTS ; 
 int /*<<< orphan*/  av_free (struct AVTEA*) ; 
 struct AVTEA* av_tea_alloc () ; 
 int /*<<< orphan*/  av_tea_crypt (struct AVTEA*,char const*,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_tea_init (struct AVTEA*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char const*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char const** tea_test_ct ; 
 int /*<<< orphan*/ * tea_test_key ; 
 char const** tea_test_pt ; 
 int /*<<< orphan*/  test_tea (struct AVTEA*,char const*,char const*,char const*,int,char const*,int,char*) ; 

int main(void)
{
    struct AVTEA *ctx;
    uint8_t buf[8], iv[8];
    int i;
    static const uint8_t src[32] = "HelloWorldHelloWorldHelloWorld";
    uint8_t ct[32];
    uint8_t pl[32];

    ctx = av_tea_alloc();
    if (!ctx)
        return 1;

    for (i = 0; i < TEA_NUM_TESTS; i++) {
        av_tea_init(ctx, tea_test_key[i], 64);

        test_tea(ctx, buf, tea_test_pt[i], tea_test_ct[i], 1, NULL, 0, "encryption");
        test_tea(ctx, buf, tea_test_ct[i], tea_test_pt[i], 1, NULL, 1, "decryption");

        /* encrypt */
        memcpy(iv, "HALLO123", 8);
        av_tea_crypt(ctx, ct, src, 4, iv, 0);

        /* decrypt into pl */
        memcpy(iv, "HALLO123", 8);
        test_tea(ctx, pl, ct, src, 4, iv, 1, "CBC decryption");

        memcpy(iv, "HALLO123", 8);
        test_tea(ctx, ct, ct, src, 4, iv, 1, "CBC inplace decryption");
    }

    printf("Test encryption/decryption success.\n");
    av_free(ctx);

    return 0;
}