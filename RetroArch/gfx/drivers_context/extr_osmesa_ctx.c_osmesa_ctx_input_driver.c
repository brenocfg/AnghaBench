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
typedef  int /*<<< orphan*/  input_driver_t ;

/* Variables and functions */

__attribute__((used)) static void osmesa_ctx_input_driver(void *data,
      const char *name,
      input_driver_t **input, void **input_data)
{
   *input      = NULL;
   *input_data = NULL;
}