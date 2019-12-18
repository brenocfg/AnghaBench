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

/* Variables and functions */
 int /*<<< orphan*/  INPUT ; 
 int /*<<< orphan*/  OUTPUT ; 
 int /*<<< orphan*/  PERIPH_RMT_MODULE ; 
 scalar_t__ RMT_SIG_IN0_IDX ; 
 scalar_t__ RMT_SIG_OUT0_IDX ; 
 int periph_enabled ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinMatrixInAttach (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinMatrixOutAttach (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinMode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _initPin(int pin, int channel, bool tx_not_rx) 
{
    if (!periph_enabled) {
        periph_enabled = true;
        periph_module_enable( PERIPH_RMT_MODULE );
    }
    if (tx_not_rx) {
        pinMode(pin, OUTPUT);
        pinMatrixOutAttach(pin, RMT_SIG_OUT0_IDX + channel, 0, 0);
    } else {
        pinMode(pin, INPUT);
        pinMatrixInAttach(pin, RMT_SIG_IN0_IDX + channel, 0);

    }
}