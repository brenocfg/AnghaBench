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
struct TYPE_3__ {int /*<<< orphan*/  metadata_size; scalar_t__ out; } ;
typedef  TYPE_1__ OutputStream ;

/* Variables and functions */
 int /*<<< orphan*/  avio_write (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int parse_header (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hds_write(void *opaque, uint8_t *buf, int buf_size)
{
    OutputStream *os = opaque;
    if (os->out) {
        avio_write(os->out, buf, buf_size);
    } else {
        if (!os->metadata_size) {
            int ret;
            // Assuming the IO buffer is large enough to fit the
            // FLV header and all metadata and extradata packets
            if ((ret = parse_header(os, buf, buf_size)) < 0)
                return ret;
        }
    }
    return buf_size;
}