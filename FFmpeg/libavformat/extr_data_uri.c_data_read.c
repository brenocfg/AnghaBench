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
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {scalar_t__ pos; scalar_t__ size; scalar_t__ data; } ;
typedef  TYPE_2__ DataContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFMIN (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 

__attribute__((used)) static int data_read(URLContext *h, unsigned char *buf, int size)
{
    DataContext *dc = h->priv_data;

    if (dc->pos >= dc->size)
        return AVERROR_EOF;
    size = FFMIN(size, dc->size - dc->pos);
    memcpy(buf, dc->data + dc->pos, size);
    dc->pos += size;
    return size;
}