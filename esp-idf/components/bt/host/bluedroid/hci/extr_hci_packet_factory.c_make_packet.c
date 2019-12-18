#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t len; scalar_t__ layer_specific; scalar_t__ offset; scalar_t__ event; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ osi_calloc (int) ; 

__attribute__((used)) static BT_HDR *make_packet(size_t data_size)
{
    BT_HDR *ret = (BT_HDR *)osi_calloc(sizeof(BT_HDR) + data_size);
    assert(ret);
    ret->event = 0;
    ret->offset = 0;
    ret->layer_specific = 0;
    ret->len = data_size;
    return ret;
}