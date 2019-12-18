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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ is_token_delimiter (char const) ; 

__attribute__((used)) static boolean_t
is_token_break(const char *str) 
{
    /* This is safe because '\0' is a token delimiter, so the second check
     * will not execute if we reach the end of the string.
     */
    return (!is_token_delimiter(str[0]) && is_token_delimiter(str[1]));
}