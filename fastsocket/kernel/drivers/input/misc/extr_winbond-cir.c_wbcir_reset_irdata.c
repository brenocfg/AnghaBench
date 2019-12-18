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
struct wbcir_data {scalar_t__ irdata_error; scalar_t__ irdata_off; scalar_t__ irdata_count; int /*<<< orphan*/  irdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wbcir_reset_irdata(struct wbcir_data *data)
{
	memset(data->irdata, 0, sizeof(data->irdata));
	data->irdata_count = 0;
	data->irdata_off = 0;
	data->irdata_error = 0;
}