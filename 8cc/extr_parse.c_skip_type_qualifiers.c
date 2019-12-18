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
 int /*<<< orphan*/  KCONST ; 
 int /*<<< orphan*/  KRESTRICT ; 
 int /*<<< orphan*/  KVOLATILE ; 
 scalar_t__ next_token (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skip_type_qualifiers() {
    while (next_token(KCONST) || next_token(KVOLATILE) || next_token(KRESTRICT));
}