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
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 int /*<<< orphan*/ * make_keyword (int) ; 
 scalar_t__ next (char) ; 

__attribute__((used)) static Token *read_rep2(char expect1, int t1, char expect2, int t2, char els) {
    if (next(expect1))
        return make_keyword(t1);
    return make_keyword(next(expect2) ? t2 : els);
}