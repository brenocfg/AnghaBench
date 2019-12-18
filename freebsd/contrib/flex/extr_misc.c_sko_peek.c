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
struct TYPE_2__ {int dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  flex_die (char*) ; 
 int sko_len ; 
 TYPE_1__* sko_stack ; 

__attribute__((used)) static void sko_peek(bool *dc)
{
    if(sko_len <= 0)
        flex_die("peek attempt when sko stack is empty");
    if(dc)
        *dc = sko_stack[sko_len-1].dc;
}