#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ window_size; } ;
struct TYPE_5__ {scalar_t__ segment_index; scalar_t__ nb_segments; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ DASHContext ;

/* Variables and functions */
 int FFMAX (scalar_t__,int) ; 

__attribute__((used)) static void get_start_index_number(OutputStream *os, DASHContext *c,
                                   int *start_index, int *start_number) {
    *start_index = 0;
    *start_number = 1;
    if (c->window_size) {
        *start_index  = FFMAX(os->nb_segments   - c->window_size, 0);
        *start_number = FFMAX(os->segment_index - c->window_size, 1);
    }
}