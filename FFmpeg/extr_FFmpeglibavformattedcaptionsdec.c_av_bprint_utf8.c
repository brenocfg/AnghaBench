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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,unsigned int,int) ; 
 int av_log2 (unsigned int) ; 

__attribute__((used)) static void av_bprint_utf8(AVBPrint *bp, unsigned c)
{
    int bytes, i;

    if (c <= 0x7F) {
        av_bprint_chars(bp, c, 1);
        return;
    }
    bytes = (av_log2(c) - 2) / 5;
    av_bprint_chars(bp, (c >> (bytes * 6)) | ((0xFF80 >> bytes) & 0xFF), 1);
    for (i = bytes - 1; i >= 0; i--)
        av_bprint_chars(bp, ((c >> (i * 6)) & 0x3F) | 0x80, 1);
}