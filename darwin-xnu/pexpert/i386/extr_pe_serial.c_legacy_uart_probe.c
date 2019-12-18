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
 int IO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCR ; 

__attribute__((used)) static int
legacy_uart_probe( void )
{
    /* Verify that the Scratch Register is accessible */

    IO_WRITE( SCR, 0x5a );
    if (IO_READ(SCR) != 0x5a) return 0;
    IO_WRITE( SCR, 0xa5 );
    if (IO_READ(SCR) != 0xa5) return 0;
    return 1;
}