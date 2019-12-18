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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void bprint_bytes(AVBPrint *bp, const uint8_t *ubuf, size_t ubuf_size)
{
    int i;
    av_bprintf(bp, "0X");
    for (i = 0; i < ubuf_size; i++)
        av_bprintf(bp, "%02X", ubuf[i]);
}