#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* realm; } ;
typedef  TYPE_1__ HTTPAuthState ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static void handle_basic_params(HTTPAuthState *state, const char *key,
                                int key_len, char **dest, int *dest_len)
{
    if (!strncmp(key, "realm=", key_len)) {
        *dest     =        state->realm;
        *dest_len = sizeof(state->realm);
    }
}