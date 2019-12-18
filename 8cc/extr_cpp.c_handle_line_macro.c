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
struct TYPE_6__ {TYPE_1__* file; } ;
typedef  TYPE_2__ Token ;
struct TYPE_5__ {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  TNUMBER ; 
 int /*<<< orphan*/  format (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_token_pushback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_line_macro(Token *tmpl) {
    make_token_pushback(tmpl, TNUMBER, format("%d", tmpl->file->line));
}