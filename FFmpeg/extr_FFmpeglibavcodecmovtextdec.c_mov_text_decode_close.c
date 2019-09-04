#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  MovTextContext ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  mov_text_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_text_cleanup_ftab (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_text_decode_close(AVCodecContext *avctx)
{
    MovTextContext *m = avctx->priv_data;
    mov_text_cleanup_ftab(m);
    mov_text_cleanup(m);
    return 0;
}