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
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  buf_printf (char*,char*,...) ; 
 scalar_t__ flag_nolinesync ; 
 char* gen_buf ; 
 int /*<<< orphan*/  gen_str (int /*<<< orphan*/ ,int) ; 

void gen_buf_pos(char **pbuf, SrcPos pos) {
    if (flag_nolinesync) {
        return;
    }
    char *buf = *pbuf;
    buf_printf(buf, "\n#line %d ", pos.line);
    char *old_gen_buf = gen_buf;
    gen_buf = buf;
    gen_str(pos.name, false);
    buf = gen_buf;
    gen_buf = old_gen_buf;
    buf_printf(buf, "\n");
    *pbuf = buf;
}