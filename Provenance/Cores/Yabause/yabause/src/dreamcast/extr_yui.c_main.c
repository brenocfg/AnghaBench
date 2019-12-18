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
 int /*<<< orphan*/  BFONT_CODE_ISO8859_1 ; 
 int DoGui () ; 
 int /*<<< orphan*/  YuiInit (int) ; 
 int /*<<< orphan*/  bfont_set_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[])    {
    int core;

    printf("...\n");

    bfont_set_encoding(BFONT_CODE_ISO8859_1);
    core = DoGui();
    YuiInit(core);

    return 0;
}