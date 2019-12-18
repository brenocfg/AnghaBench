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
struct TYPE_4__ {void* priv_data; TYPE_1__* prot; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_3__ {scalar_t__ priv_data_class; } ;

/* Variables and functions */

__attribute__((used)) static void *urlcontext_child_next(void *obj, void *prev)
{
    URLContext *h = obj;
    if (!prev && h->priv_data && h->prot->priv_data_class)
        return h->priv_data;
    return NULL;
}