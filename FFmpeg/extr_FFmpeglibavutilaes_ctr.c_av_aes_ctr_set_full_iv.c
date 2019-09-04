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
struct AVAESCTR {scalar_t__ block_offset; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void av_aes_ctr_set_full_iv(struct AVAESCTR *a, const uint8_t* iv)
{
    memcpy(a->counter, iv, sizeof(a->counter));
    a->block_offset = 0;
}