#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* codec; } ;
struct TYPE_3__ {scalar_t__ decode; } ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVClassCategory ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CLASS_CATEGORY_DECODER ; 
 int /*<<< orphan*/  AV_CLASS_CATEGORY_ENCODER ; 

__attribute__((used)) static AVClassCategory get_category(void *ptr)
{
    AVCodecContext* avctx = ptr;
    if(avctx->codec && avctx->codec->decode) return AV_CLASS_CATEGORY_DECODER;
    else                                     return AV_CLASS_CATEGORY_ENCODER;
}