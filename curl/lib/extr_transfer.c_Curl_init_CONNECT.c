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
struct TYPE_4__ {int /*<<< orphan*/  in_set; int /*<<< orphan*/  fread_func_set; } ;
struct TYPE_3__ {int /*<<< orphan*/  in; int /*<<< orphan*/  fread_func; } ;
struct Curl_easy {TYPE_2__ set; TYPE_1__ state; } ;

/* Variables and functions */

void Curl_init_CONNECT(struct Curl_easy *data)
{
  data->state.fread_func = data->set.fread_func_set;
  data->state.in = data->set.in_set;
}