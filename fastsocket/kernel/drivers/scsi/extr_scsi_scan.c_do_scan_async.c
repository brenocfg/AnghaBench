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
struct async_scan_data {int /*<<< orphan*/  shost; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_scsi_scan_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_finish_async_scan (struct async_scan_data*) ; 

__attribute__((used)) static void do_scan_async(void *_data, async_cookie_t c)
{
	struct async_scan_data *data = _data;
	do_scsi_scan_host(data->shost);
	scsi_finish_async_scan(data);
}