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
struct TYPE_3__ {int /*<<< orphan*/  pack_line_10; int /*<<< orphan*/  pack_line_8; } ;
typedef  TYPE_1__ V210EncContext ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_pack_line (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_v210enc_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  uint16_t ; 
 int /*<<< orphan*/  uint8_t ; 

void checkasm_check_v210enc(void)
{
    V210EncContext h;

    ff_v210enc_init(&h);

    if (check_func(h.pack_line_8, "v210_planar_pack_8"))
        check_pack_line(uint8_t, 0xffffffff);

    if (check_func(h.pack_line_10, "v210_planar_pack_10"))
        check_pack_line(uint16_t, 0x03ff03ff);

    report("planar_pack");
}