#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cb_data {int remaining_bytes; scalar_t__ paused; scalar_t__ response_received; int /*<<< orphan*/ * easy_handle; } ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */

__attribute__((used)) static void reset_data(struct cb_data *data, CURL *curl)
{
  data->easy_handle = curl;
  data->response_received = 0;
  data->paused = 0;
  data->remaining_bytes = 3;
}