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
typedef  int gint ;
typedef  char gchar ;

/* Variables and functions */
#define  CAMEL_FIRST_UPPER 129 
#define  CAMEL_OTHER 128 

__attribute__((used)) static void
camel_convert(gchar *str)
{
    gint state = CAMEL_OTHER;

    if (str == NULL) return;
    while (*str)
    {
        if (*str == '_') *str = ' ';
        switch (state)
        {
            case CAMEL_OTHER:
            {
                if (*str >= 'A' && *str <= 'Z')
                    state = CAMEL_FIRST_UPPER;
                else
                    state = CAMEL_OTHER;

            } break;
            case CAMEL_FIRST_UPPER:
            {
                if (*str >= 'A' && *str <= 'Z')
                    *str = *str - 'A' + 'a';
                else
                    state = CAMEL_OTHER;
            } break;
        }
        str++;
    }
}