#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* name; int line; } ;
struct TYPE_4__ {TYPE_1__ pos; } ;

/* Variables and functions */
 char const* line_start ; 
 int /*<<< orphan*/  next_token () ; 
 char const* stream ; 
 TYPE_2__ token ; 

void init_stream(const char *name, const char *buf) {
    stream = buf;
    line_start = stream;
    token.pos.name = name ? name : "<string>";
    token.pos.line = 1;
    next_token();
}