#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cleanup; int /*<<< orphan*/  datalen; scalar_t__ data; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_copy_size (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* zbar_image_create () ; 
 int /*<<< orphan*/  zbar_image_free_data ; 

zbar_image_t *zbar_image_copy (const zbar_image_t *src)
{
    zbar_image_t *dst = zbar_image_create();
    dst->format = src->format;
    _zbar_image_copy_size(dst, src);
    dst->datalen = src->datalen;
    dst->data = malloc(src->datalen);
    assert(dst->data);
    memcpy((void*)dst->data, src->data, src->datalen);
    dst->cleanup = zbar_image_free_data;
    return(dst);
}