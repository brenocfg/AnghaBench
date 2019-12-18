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
typedef  int /*<<< orphan*/  mz_zip_reader_entry_cb ;
struct TYPE_2__ {void* entry_userdata; int /*<<< orphan*/  entry_cb; } ;
typedef  TYPE_1__ mz_zip_reader ;

/* Variables and functions */

void mz_zip_reader_set_entry_cb(void *handle, void *userdata, mz_zip_reader_entry_cb cb)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    reader->entry_cb = cb;
    reader->entry_userdata = userdata;
}