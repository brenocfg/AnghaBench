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
struct Curl_easy {TYPE_2__* multi; TYPE_1__* multi_easy; } ;
struct TYPE_4__ {int in_callback; } ;
struct TYPE_3__ {int in_callback; } ;

/* Variables and functions */

void Curl_set_in_callback(struct Curl_easy *data, bool value)
{
  /* might get called when there is no data pointer! */
  if(data) {
    if(data->multi_easy)
      data->multi_easy->in_callback = value;
    else if(data->multi)
      data->multi->in_callback = value;
  }
}