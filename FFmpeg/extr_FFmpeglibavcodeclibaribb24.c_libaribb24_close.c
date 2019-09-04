#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ lib_instance; scalar_t__ decoder; } ;
typedef  TYPE_1__ Libaribb24Context ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  arib_finalize_decoder (scalar_t__) ; 
 int /*<<< orphan*/  arib_instance_destroy (scalar_t__) ; 

__attribute__((used)) static int libaribb24_close(AVCodecContext *avctx)
{
    Libaribb24Context *b24 = avctx->priv_data;

    if (b24->decoder)
        arib_finalize_decoder(b24->decoder);

    if (b24->lib_instance)
        arib_instance_destroy(b24->lib_instance);

    return 0;
}