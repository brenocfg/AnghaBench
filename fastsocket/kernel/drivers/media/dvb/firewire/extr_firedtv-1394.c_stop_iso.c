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
struct hpsb_iso {int dummy; } ;
struct firedtv {struct hpsb_iso* backend_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpsb_iso_shutdown (struct hpsb_iso*) ; 
 int /*<<< orphan*/  hpsb_iso_stop (struct hpsb_iso*) ; 

__attribute__((used)) static void stop_iso(struct firedtv *fdtv)
{
	struct hpsb_iso *iso_handle = fdtv->backend_data;

	if (iso_handle != NULL) {
		hpsb_iso_stop(iso_handle);
		hpsb_iso_shutdown(iso_handle);
	}
	fdtv->backend_data = NULL;
}