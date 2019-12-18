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
struct TYPE_3__ {int /*<<< orphan*/ * uo; int /*<<< orphan*/ * ug; int /*<<< orphan*/ * ui; int /*<<< orphan*/ * uf; int /*<<< orphan*/ * wo; int /*<<< orphan*/ * wg; int /*<<< orphan*/ * wi; int /*<<< orphan*/ * wf; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  update_connected_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_lstm_layer(layer l, update_args a)
{
    update_connected_layer(*(l.wf), a);
    update_connected_layer(*(l.wi), a);
    update_connected_layer(*(l.wg), a);
    update_connected_layer(*(l.wo), a);
    update_connected_layer(*(l.uf), a);
    update_connected_layer(*(l.ui), a);
    update_connected_layer(*(l.ug), a);
    update_connected_layer(*(l.uo), a);
}