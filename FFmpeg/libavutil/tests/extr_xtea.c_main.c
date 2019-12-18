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
typedef  int /*<<< orphan*/  AVXTEA ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB32 (char const*) ; 
 int /*<<< orphan*/  AV_WL32 (char const*,int /*<<< orphan*/ ) ; 
 int XTEA_NUM_TESTS ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_xtea_alloc () ; 
 int /*<<< orphan*/  av_xtea_crypt (int /*<<< orphan*/ *,char const*,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_xtea_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  av_xtea_le_crypt (int /*<<< orphan*/ *,char const*,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_xtea_le_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memcpy (char const*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_xtea (int /*<<< orphan*/ *,char const*,char const*,char const*,int,char const*,int,char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,char const*,char const*,int,char const*,int /*<<< orphan*/ )) ; 
 char const** xtea_test_ct ; 
 char const** xtea_test_key ; 
 char const** xtea_test_pt ; 

int main(void)
{
    uint8_t buf[16], iv[8];
    int i, j;
    static const uint8_t src[32] = "HelloWorldHelloWorldHelloWorld";
    uint8_t ct[32];
    uint8_t pl[32];
    AVXTEA *ctx = av_xtea_alloc();
    if (!ctx)
        return 1;

    for (i = 0; i < XTEA_NUM_TESTS; i++) {
        av_xtea_init(ctx, xtea_test_key[i]);

        test_xtea(ctx, buf, xtea_test_pt[i], xtea_test_ct[i], 1, NULL, 0, "encryption", av_xtea_crypt);
        test_xtea(ctx, buf, xtea_test_ct[i], xtea_test_pt[i], 1, NULL, 1, "decryption", av_xtea_crypt);

        for (j = 0; j < 4; j++)
            AV_WL32(&buf[4*j], AV_RB32(&xtea_test_key[i][4*j]));
        av_xtea_le_init(ctx, buf);
        for (j = 0; j < 2; j++) {
            AV_WL32(&ct[4*j], AV_RB32(&xtea_test_ct[i][4*j]));
            AV_WL32(&pl[4*j], AV_RB32(&xtea_test_pt[i][4*j]));
        }
        test_xtea(ctx, buf, pl, ct, 1, NULL, 0, "encryption", av_xtea_le_crypt);
        test_xtea(ctx, buf, ct, pl, 1, NULL, 1, "decryption", av_xtea_le_crypt);

        /* encrypt */
        memcpy(iv, "HALLO123", 8);
        av_xtea_crypt(ctx, ct, src, 4, iv, 0);

        /* decrypt into pl */
        memcpy(iv, "HALLO123", 8);
        test_xtea(ctx, pl, ct, src, 4, iv, 1, "CBC decryption", av_xtea_crypt);

        memcpy(iv, "HALLO123", 8);
        test_xtea(ctx, ct, ct, src, 4, iv, 1, "CBC inplace decryption", av_xtea_crypt);
    }

    printf("Test encryption/decryption success.\n");
    av_free(ctx);

    return 0;
}