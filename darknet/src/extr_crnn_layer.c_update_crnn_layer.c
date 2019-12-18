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
struct TYPE_3__ {int /*<<< orphan*/ * output_layer; int /*<<< orphan*/ * self_layer; int /*<<< orphan*/ * input_layer; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  update_convolutional_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_crnn_layer(layer l, update_args a)
{
    update_convolutional_layer(*(l.input_layer),  a);
    update_convolutional_layer(*(l.self_layer),   a);
    update_convolutional_layer(*(l.output_layer), a);
}