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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ hb_mixdown_has_codec_support (int,int /*<<< orphan*/ ) ; 
 scalar_t__ hb_mixdown_has_remix_support (int,int /*<<< orphan*/ ) ; 

int hb_mixdown_is_supported(int mixdown, uint32_t codec, uint64_t layout)
{
    return (hb_mixdown_has_codec_support(mixdown, codec) &&
            hb_mixdown_has_remix_support(mixdown, layout));
}