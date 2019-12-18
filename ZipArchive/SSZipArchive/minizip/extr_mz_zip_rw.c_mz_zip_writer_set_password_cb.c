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
typedef  int /*<<< orphan*/  mz_zip_writer_password_cb ;
struct TYPE_2__ {void* password_userdata; int /*<<< orphan*/  password_cb; } ;
typedef  TYPE_1__ mz_zip_writer ;

/* Variables and functions */

void mz_zip_writer_set_password_cb(void *handle, void *userdata, mz_zip_writer_password_cb cb)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    writer->password_cb = cb;
    writer->password_userdata = userdata;
}