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
struct TYPE_4__ {int /*<<< orphan*/  c; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ Libdav1dContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  dav1d_data_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dav1d_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void libdav1d_flush(AVCodecContext *c)
{
    Libdav1dContext *dav1d = c->priv_data;

    dav1d_data_unref(&dav1d->data);
    dav1d_flush(dav1d->c);
}