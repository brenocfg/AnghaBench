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
struct AVAESCTR {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_aes_ctr_set_iv (struct AVAESCTR*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_get_random_seed () ; 

void av_aes_ctr_set_random_iv(struct AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}