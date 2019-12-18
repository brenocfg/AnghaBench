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
 int /*<<< orphan*/  printf (char*) ; 

void print_options(void)
{
    printf(" -vdriver <s>        \t Select video driver (auto)\n");
    printf(" -res <w> <h>        \t Specify display resolution (320x240)\n");
    printf(" -depth <n>          \t Specify display depth (8)\n");
    printf(" -remap <on|off>     \t Enable raster-based palette effects (8-bit color only)\n");
    printf(" -scanlines <on|off> \t Enable scanlines effect\n");
    printf(" -scale <on|off>     \t Scale display to width of screen\n");
    printf(" -vsync <on|off>     \t Enable vsync polling\n");
    printf(" -throttle <on|off>  \t Enable speed throttling\n");
    printf(" -skip <n>           \t Specify frame skip level (1=no frames skipped)\n");
    printf(" -sound <on|off>     \t Enable sound output\n");
    printf(" -sndcard <n>        \t Select sound card\n");
    printf(" -sndrate <n>        \t Specify sound sample rate (8000-44100)\n");
    printf(" -swap <on|off>      \t Swap left and right channels\n");
    printf(" -joy <s>            \t Select joystick driver (auto)\n");
}