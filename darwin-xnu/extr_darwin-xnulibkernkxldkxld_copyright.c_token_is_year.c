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
typedef  int u_int ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int kYearLen ; 

__attribute__((used)) static boolean_t
token_is_year(const char *str)
{
    boolean_t result = FALSE;
    u_int i = 0;

    for (i = 0; i < kYearLen - 1; ++i) {
        if (str[i] < '0' || str[i] > '9') goto finish;
    }

    if (str[i] != '\0') goto finish;
    
    result = TRUE;
finish:
    return result;
}