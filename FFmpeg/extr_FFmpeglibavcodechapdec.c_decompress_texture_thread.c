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
 int decompress_texture_thread_internal (int /*<<< orphan*/ *,void*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decompress_texture_thread(AVCodecContext *avctx, void *arg,
                                     int slice, int thread_nb)
{
    return decompress_texture_thread_internal(avctx, arg, slice, thread_nb, 0);
}