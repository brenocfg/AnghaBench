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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  frame_size_read; int /*<<< orphan*/  frame_size_write; } ;

/* Variables and functions */
 int execute_spi_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ ssp_configuration ; 

__attribute__((used)) static int ssp_write_read (u16 data)
{
	return execute_spi_command (data, ssp_configuration.frame_size_write,
				    ssp_configuration.frame_size_read);
}