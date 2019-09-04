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
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ASS_DEFAULT_ALIGNMENT ; 
 int /*<<< orphan*/  ASS_DEFAULT_BACK_COLOR ; 
 int /*<<< orphan*/  ASS_DEFAULT_BOLD ; 
 int /*<<< orphan*/  ASS_DEFAULT_BORDERSTYLE ; 
 int /*<<< orphan*/  ASS_DEFAULT_COLOR ; 
 int /*<<< orphan*/  ASS_DEFAULT_FONT ; 
 int /*<<< orphan*/  ASS_DEFAULT_FONT_SIZE ; 
 int /*<<< orphan*/  ASS_DEFAULT_ITALIC ; 
 int /*<<< orphan*/  ASS_DEFAULT_UNDERLINE ; 
 int ff_ass_subtitle_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_ass_subtitle_header_default(AVCodecContext *avctx)
{
    return ff_ass_subtitle_header(avctx, ASS_DEFAULT_FONT,
                               ASS_DEFAULT_FONT_SIZE,
                               ASS_DEFAULT_COLOR,
                               ASS_DEFAULT_BACK_COLOR,
                               ASS_DEFAULT_BOLD,
                               ASS_DEFAULT_ITALIC,
                               ASS_DEFAULT_UNDERLINE,
                               ASS_DEFAULT_BORDERSTYLE,
                               ASS_DEFAULT_ALIGNMENT);
}