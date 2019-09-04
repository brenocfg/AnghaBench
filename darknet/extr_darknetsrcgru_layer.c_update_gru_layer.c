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
typedef  int /*<<< orphan*/  update_args ;
struct TYPE_3__ {int /*<<< orphan*/ * wh; int /*<<< orphan*/ * wz; int /*<<< orphan*/ * wr; int /*<<< orphan*/ * uh; int /*<<< orphan*/ * uz; int /*<<< orphan*/ * ur; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  update_connected_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_gru_layer(layer l, update_args a)
{
    update_connected_layer(*(l.ur), a);
    update_connected_layer(*(l.uz), a);
    update_connected_layer(*(l.uh), a);
    update_connected_layer(*(l.wr), a);
    update_connected_layer(*(l.wz), a);
    update_connected_layer(*(l.wh), a);
}