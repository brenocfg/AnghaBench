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
struct TYPE_4__ {int beg; int end; char* label; } ;
typedef  TYPE_1__ Case ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static Case *make_case(int beg, int end, char *label) {
    Case *r = malloc(sizeof(Case));
    r->beg = beg;
    r->end = end;
    r->label = label;
    return r;
}