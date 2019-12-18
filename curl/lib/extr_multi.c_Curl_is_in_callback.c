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
struct Curl_easy {TYPE_2__* multi_easy; TYPE_1__* multi; } ;
struct TYPE_4__ {scalar_t__ in_callback; } ;
struct TYPE_3__ {scalar_t__ in_callback; } ;

/* Variables and functions */

bool Curl_is_in_callback(struct Curl_easy *easy)
{
  return ((easy->multi && easy->multi->in_callback) ||
          (easy->multi_easy && easy->multi_easy->in_callback));
}