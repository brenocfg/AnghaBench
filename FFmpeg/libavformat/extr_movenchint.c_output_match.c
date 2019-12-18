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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void output_match(AVIOContext *out, int match_sample,
                         int match_offset, int match_len, int *entries)
{
    avio_w8(out, 2); /* sample constructor */
    avio_w8(out, 0); /* track reference */
    avio_wb16(out, match_len);
    avio_wb32(out, match_sample);
    avio_wb32(out, match_offset);
    avio_wb16(out, 1); /* bytes per block */
    avio_wb16(out, 1); /* samples per block */
    (*entries)++;
}