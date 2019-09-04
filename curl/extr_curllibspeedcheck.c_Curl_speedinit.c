#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct curltime {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  keeps_speed; } ;
struct Curl_easy {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void Curl_speedinit(struct Curl_easy *data)
{
  memset(&data->state.keeps_speed, 0, sizeof(struct curltime));
}