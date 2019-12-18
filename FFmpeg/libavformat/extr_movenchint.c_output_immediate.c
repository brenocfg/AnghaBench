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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void output_immediate(const uint8_t *data, int size,
                             AVIOContext *out, int *entries)
{
    while (size > 0) {
        int len = size;
        if (len > 14)
            len = 14;
        avio_w8(out, 1); /* immediate constructor */
        avio_w8(out, len); /* amount of valid data */
        avio_write(out, data, len);
        data += len;
        size -= len;

        for (; len < 14; len++)
            avio_w8(out, 0);

        (*entries)++;
    }
}