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
typedef  int /*<<< orphan*/  Vector ;

/* Variables and functions */
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unget_all(Vector *tokens) {
    for (int i = vec_len(tokens) - 1; i >= 0; i--)
        unget_token(vec_get(tokens, i));
}