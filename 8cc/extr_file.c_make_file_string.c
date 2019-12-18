#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int line; int column; char* p; } ;
typedef  TYPE_1__ File ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

File *make_file_string(char *s) {
    File *r = calloc(1, sizeof(File));
    r->line = 1;
    r->column = 1;
    r->p = s;
    return r;
}