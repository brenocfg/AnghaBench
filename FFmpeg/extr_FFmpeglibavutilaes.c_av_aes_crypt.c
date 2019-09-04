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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  rounds; int /*<<< orphan*/  (* crypt ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ AVAES ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void av_aes_crypt(AVAES *a, uint8_t *dst, const uint8_t *src,
                  int count, uint8_t *iv, int decrypt)
{
    a->crypt(a, dst, src, count, iv, a->rounds);
}