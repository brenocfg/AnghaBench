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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_NAME ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 TYPE_1__ token ; 

const char *parse_name(void) {
    const char *name = token.name;
    expect_token(TOKEN_NAME);
    return name;
}