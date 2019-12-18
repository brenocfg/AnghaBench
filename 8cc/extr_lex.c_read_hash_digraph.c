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
 char KHASHHASH ; 
 int /*<<< orphan*/ * make_keyword (char) ; 
 scalar_t__ next (char) ; 
 int /*<<< orphan*/  unreadc (char) ; 

__attribute__((used)) static Token *read_hash_digraph() {
    if (next('>'))
        return make_keyword('}');
    if (next(':')) {
        if (next('%')) {
            if (next(':'))
                return make_keyword(KHASHHASH);
            unreadc('%');
        }
        return make_keyword('#');
    }
    return NULL;
}