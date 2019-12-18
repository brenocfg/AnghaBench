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
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  maplength; int /*<<< orphan*/  p; int /*<<< orphan*/  maptype; int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ SUNRASTContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  RAS_MAGIC ; 
 int /*<<< orphan*/  bytestream2_put_be32u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunrast_image_write_header(AVCodecContext *avctx)
{
    SUNRASTContext *s = avctx->priv_data;

    bytestream2_put_be32u(&s->p, RAS_MAGIC);
    bytestream2_put_be32u(&s->p, avctx->width);
    bytestream2_put_be32u(&s->p, avctx->height);
    bytestream2_put_be32u(&s->p, s->depth);
    bytestream2_put_be32u(&s->p, s->length);
    bytestream2_put_be32u(&s->p, s->type);
    bytestream2_put_be32u(&s->p, s->maptype);
    bytestream2_put_be32u(&s->p, s->maplength);
}