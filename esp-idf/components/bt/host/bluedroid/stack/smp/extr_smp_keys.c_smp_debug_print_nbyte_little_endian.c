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
typedef  int /*<<< orphan*/  p_buf ;
typedef  int UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_TRACE_WARNING (char*,...) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

void smp_debug_print_nbyte_little_endian(UINT8 *p, const UINT8 *key_name, UINT8 len)
{
#if SMP_DEBUG == TRUE
    int     ind, x;
    int     col_count = 32;
    int     row_count;
    UINT8   p_buf[512];

    SMP_TRACE_WARNING("%s(LSB ~ MSB):\n", key_name);
    memset(p_buf, 0, sizeof(p_buf));
    row_count = len % col_count ? len / col_count + 1 : len / col_count;

    ind = 0;
    for (int row = 0; row <  row_count; row++) {
        for (int column = 0, x = 0; (ind < len) && (column < col_count); column++, ind++) {
            x += sprintf((char *)&p_buf[x], "%02x ", p[ind]);
        }
        SMP_TRACE_WARNING("  [%03d]: %s", row * col_count, p_buf);
    }
#endif
}