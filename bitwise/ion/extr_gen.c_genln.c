#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int gen_indent ; 
 TYPE_1__ gen_pos ; 
 int /*<<< orphan*/  genf (char*,int,char*) ; 

void genln(void) {
    genf("\n%.*s", gen_indent * 4, "                                                                  ");
    gen_pos.line++;
}