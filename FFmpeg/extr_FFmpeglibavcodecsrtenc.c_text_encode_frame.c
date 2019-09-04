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
typedef  int /*<<< orphan*/  AVSubtitle ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int encode_frame (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_callbacks ; 

__attribute__((used)) static int text_encode_frame(AVCodecContext *avctx,
                             unsigned char *buf, int bufsize, const AVSubtitle *sub)
{
    return encode_frame(avctx, buf, bufsize, sub, &text_callbacks);
}