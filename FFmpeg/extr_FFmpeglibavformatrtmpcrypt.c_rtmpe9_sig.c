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
typedef  int /*<<< orphan*/  uint32_t ;
struct AVBlowfish {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_blowfish_crypt_ecb (struct AVBlowfish*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_blowfish_init (struct AVBlowfish*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rtmpe9_keys ; 

__attribute__((used)) static void rtmpe9_sig(const uint8_t *in, uint8_t *out, int key_id)
{
    struct AVBlowfish ctx;
    uint32_t xl, xr;

    xl = AV_RL32(in);
    xr = AV_RL32(in + 4);

    av_blowfish_init(&ctx, rtmpe9_keys[key_id], 24);
    av_blowfish_crypt_ecb(&ctx, &xl, &xr, 0);

    AV_WL32(out, xl);
    AV_WL32(out + 4, xr);
}