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

/* Variables and functions */
 int /*<<< orphan*/  hex_dump_internal (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 

void av_hex_dump_log(void *avcl, int level, const uint8_t *buf, int size)
{
    hex_dump_internal(avcl, NULL, level, buf, size);
}