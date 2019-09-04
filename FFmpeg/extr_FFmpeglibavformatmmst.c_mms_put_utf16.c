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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int write_out_ptr; int out_buffer; } ;
typedef  TYPE_1__ MMSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_put_str16le (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ffio_init_context (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mms_put_utf16(MMSContext *mms, const uint8_t *src)
{
    AVIOContext bic;
    int size = mms->write_out_ptr - mms->out_buffer;
    int len;
    ffio_init_context(&bic, mms->write_out_ptr,
            sizeof(mms->out_buffer) - size, 1, NULL, NULL, NULL, NULL);

    len = avio_put_str16le(&bic, src);
    if (len < 0)
        return len;
    mms->write_out_ptr += len;
    return 0;
}