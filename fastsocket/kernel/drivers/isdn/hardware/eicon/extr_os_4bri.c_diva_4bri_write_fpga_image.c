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
typedef  scalar_t__ dword ;
struct TYPE_3__ {int /*<<< orphan*/  xdi_adapter; } ;
typedef  TYPE_1__ diva_os_xdi_adapter_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/ * diva_xdiLoadFileFile ; 
 scalar_t__ diva_xdiLoadFileLength ; 
 int qBri_FPGA_download (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
diva_4bri_write_fpga_image(diva_os_xdi_adapter_t * a, byte * data,
			   dword length)
{
	int ret;

	diva_xdiLoadFileFile = data;
	diva_xdiLoadFileLength = length;

	ret = qBri_FPGA_download(&a->xdi_adapter);

	diva_xdiLoadFileFile = NULL;
	diva_xdiLoadFileLength = 0;

	return (ret ? 0 : -1);
}